//start.cpp

#include "std.h"

#define SERVER_PORT 9000
#define SERVER_IP "127.0.0.1"   //192.168.0.6

//net으로부터 받은 ack 데이터 
void fun_RecvData(char* msg)
{
	int* p = (int*)msg;
	if (*p == PACK_NEWMEMBER_S)
	{
		printf("회원가입 성공\n");
	}
	else if(*p ==  PACK_NEWMEMBER_F)
	{
		printf("회원가입 실패(중복ID)\n");
	}
	if (*p == PACK_LOGIN_S)
	{
		printf("로그인 성공\n");
	}
	else if (*p == PACK_LOGIN_F)
	{
		printf("로그인 실패\n");
	}
	if (*p == PACK_LOGOUT_S)
	{
		printf("로그아웃 성공\n");
	}
	else if (*p == PACK_LOGOUT_F)
	{
		printf("로그아웃 실패\n");
	}
	if (*p == PACK_DELETEMEMBER_S)
	{
		printf("회원탈퇴 성공\n");
	}
	else if (*p == PACK_DELETEMEMBER_F)
	{
		printf("회원탈퇴 실패\n");
	}
}

void fun_NewMember()
{
	printf("[회원가입 정보 입력] \n\n");
	char id[20], pw[20], name[20];

	printf("아이디 : ");			gets_s(id, sizeof(id));
	printf("패스워드 : ");		gets_s(pw, sizeof(pw));
	printf("이름 : ");			gets_s(name, sizeof(name));

	//서버로 전송할 패킷을 생성!
	NEWMEMBER packet = pack_NewMember(id, pw, name);

	//서버로 전송
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("전송 오류\n");
	}
	else
	{
		printf("전송 성공\n");
	}
}

void fun_Login()
{
	printf("[로그인 정보 입력] \n\n");
	char id[20], pw[20];

	printf("아이디 : ");			gets_s(id, sizeof(id));
	printf("패스워드 : ");		gets_s(pw, sizeof(pw));

	//서버로 전송할 패킷을 생성!
	LOGIN packet = pack_Login(id, pw);

	//서버로 전송
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("전송 오류\n");
	}
	else
	{
		printf("전송 성공\n");
	}
}

void fun_Logout()
{
	printf("[로그아웃 정보 입력] \n\n");
	char id[20];

	printf("아이디 : ");			gets_s(id, sizeof(id));

	//서버로 전송할 패킷을 생성!
	LOGIN packet = pack_Logout(id);

	//서버로 전송
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("전송 오류\n");
	}
	else
	{
		printf("전송 성공\n");
	}
}

void fun_DeleteMember()
{
	printf("[회원탈퇴 정보 입력] \n\n");
	char id[20];

	printf("아이디 : ");			gets_s(id, sizeof(id));

	//서버로 전송할 패킷을 생성!
	LOGIN packet = pack_DeleteMember(id);

	//서버로 전송
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("전송 오류\n");
	}
	else
	{
		printf("전송 성공\n");
	}
}

void Run()
{
	while (true)
	{
		printf("--------------------------------------------------------------------\n");
		printf("[0] 프로그램종료 [1] 회원가입 [2] 로그인 [3] 로그아웃 [4] 회원탈퇴\n");
		printf("--------------------------------------------------------------------\n");
		switch (_getch())		//#include <conio.h>
		{
		case '0':   return;
		case '1':	fun_NewMember();		break;
		case '2':	fun_Login();			break;
		case '3':	fun_Logout();			break;
		case '4':	fun_DeleteMember();		break;
		}			
		Sleep(1000);
	}
}

int main()
{
	//---------------- 초기화 ------------------------------
	if (wbnet_LibraryInit() == 0)
	{
		printf("라이브러리 초기화 오류\n");
		return 0;
	}

	if (wbnet_CreateSocket() == 0)
	{
		printf("소켓 생성 에러\n");
		return 0;
	}

	//---------------- 실행 ------------------------------
	if (wbnet_Run(SERVER_PORT, SERVER_IP) == 0)
	{
		printf("서버 연결 실패\n");
		return 0;
	}

	Run();

	//---------------- 종료처리 ------------------------------
	wbnet_DeleteSocket();

	wbnet_LibraryExit();

	return 0;
}