//wbnet.cpp

#include "std.h"

SOCKET clientSocket;

void fun_RecvData(char* msg);


int wbnet_LibraryInit()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //버전 초기화(2.2버전)
	{
		return 0;
	}
	return 1;
}

int wbnet_CreateSocket()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // SOCK_DGRAM --> IPPROTO_UDP
	if (clientSocket == INVALID_SOCKET)
	{
		return 0;
	}
	return 1;
}

void wbnet_DeleteSocket()
{
	closesocket(clientSocket);
}

void wbnet_LibraryExit()
{
	WSACleanup();
}

int wbnet_Run(int port, const char* ip)
{
	//2. 연결 요청(연결할 서버의 주소)
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip); //문자열 -> 숫자 -> NetworkByteOrder로 변경

	int retval = connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
	{
		return 0;
	}

	printf("서버 연결 성공\n");
	_beginthreadex(0, 0, ReciveThread, (void*)clientSocket, 0, 0);

	return 1;
}

int wbnet_SendData(const char* msg, int size)
{
	int rev = wbsend(clientSocket, (char*)msg, size);
	if (rev == SOCKET_ERROR)
		return -1;
	else
		return rev;
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

unsigned int __stdcall ReciveThread(void* param)
{
	SOCKET sock = (SOCKET)param;
	char buf[512];
	int size;

	//수신
	while (true)
	{
		ZeroMemory(buf, sizeof(buf));
		size = wbrecive(sock, buf);
		if (size == SOCKET_ERROR || size == 0)
		{
			printf("연결 파이프가 끊어짐 or 서버 통신 소켓 종료\n");
			break;
		}
		else
		{
			fun_RecvData(buf);
			//printf("(%dbyte수신) %s\n", size, buf);
		}
	}
	closesocket(sock);
	return 0;
}
