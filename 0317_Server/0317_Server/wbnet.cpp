//wbnet.cpp

#include "std.h"

SOCKET listenSocket;
vector<SOCKET> g_sockets;

void fun_RecvData(char* msg);		//<----------------------------------


int wbnet_LibraryInit()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //버전 초기화(2.2버전)
	{
		return 0;
	}
	return 1;
}

int wbnet_CreateListenSocket(int port)
{
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // SOCK_DGRAM --> IPPROTO_UDP
	if (listenSocket == INVALID_SOCKET)
	{
		printf("소켓 생성 에러\n");
		return -1;
	}

	//2. 주소 할당(SOCKADDR) (SOCKADDR_IN)
	SOCKADDR_IN addr = { 0 };
	memset(&addr, 0, sizeof(addr));  //C 함수
	ZeroMemory(&addr, sizeof(addr)); //소켓 라이브러리 함수

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);   //cmd >> ipconfig >> 192.168.0.6

	int retval = bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
	{
		printf("주소 연결 실패\n");
		return -1;
	}

	//3. 망 연결
	retval = listen(listenSocket, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		printf("망 연결 실패\n");
		return -1;
	}

	return 1;
}

void wbnet_DeleteListenSocket()
{
	closesocket(listenSocket);
}

void wbnet_LibraryExit()
{
	WSACleanup();
}

void wbnet_ServerRun()
{
	while (true)
	{
		//4. 접속 대기
		SOCKADDR_IN clientaddr;
		int clientaddrlen = sizeof(clientaddr);

		SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientaddr, &clientaddrlen);
		if (clientSocket == INVALID_SOCKET)
		{
			printf("클라이언트 연결 실패\n");
			continue;
		}

		g_sockets.push_back(clientSocket);  //<--------------------(1)

		printf("클라이언트 접속 : %s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		_beginthreadex(0, 0, WorkThread, (void*)clientSocket, 0, 0);
	}
}

unsigned int __stdcall WorkThread(void* param)
{
	SOCKET clientSocket = (SOCKET)param;

	while (true)
	{
		//--데이터 수신--
		char buf[512];
		int  size;

		size = wbrecive(clientSocket, buf);
		if (size == SOCKET_ERROR)
		{
			printf("수신 오류\n");   break;
		}
		else if (size == 0)
		{
			printf("상대방이 소켓을 closesocket()함\n");  break;
		}
		else
		{
			fun_RecvData(buf);				//<-------------------------------

			//클라이언트에 송신
			wbsend(clientSocket, buf, size);

			//for (int i = 0; i < (int)g_sockets.size(); i++)
			//{
			//	SOCKET sock = g_sockets[i];
			//	wbsend(sock, buf, strlen(buf) + 1);				//(3)사용
			//}
		}
	}

	for (int i = 0; i < (int)g_sockets.size(); i++)
	{
		SOCKET sock = g_sockets[i];
		if (sock == clientSocket)
		{
			g_sockets.erase(g_sockets.begin() + i);         //(2)삭제
			break;
		}
	}

	//clientSocket을 통해서 상대방 주소 획득!
	SOCKADDR_IN clientaddr;
	int length = sizeof(clientaddr);
	getpeername(clientSocket, (sockaddr*)&clientaddr, &length);
	printf("클라이언트 해제 : %s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(clientSocket);

	return 0;
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;   //8  5   1  0

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}

int wbsend(SOCKET s, char* buf, int len)
{
	//헤더
	send(s, (char*)&len, sizeof(int), 0);
	//본 데이터
	return send(s, buf, len, 0);
}

int wbrecive(SOCKET s, char* buf)
{
	//헤더 
	int size;
	recvn(s, (char*)&size, sizeof(int), 0);

	//본데이터
	return recvn(s, (char*)buf, size, 0);
}

