//start.cpp

#include "std.h"

#define SERVER_PORT 9000
#define SERVER_IP "127.0.0.1"   //192.168.0.6

//net���κ��� ���� ack ������ 
void fun_RecvData(char* msg)
{
	int* p = (int*)msg;
	if (*p == PACK_NEWMEMBER_S)
	{
		printf("ȸ������ ����\n");
	}
	else if(*p ==  PACK_NEWMEMBER_F)
	{
		printf("ȸ������ ����(�ߺ�ID)\n");
	}
	if (*p == PACK_LOGIN_S)
	{
		printf("�α��� ����\n");
	}
	else if (*p == PACK_LOGIN_F)
	{
		printf("�α��� ����\n");
	}
	if (*p == PACK_LOGOUT_S)
	{
		printf("�α׾ƿ� ����\n");
	}
	else if (*p == PACK_LOGOUT_F)
	{
		printf("�α׾ƿ� ����\n");
	}
	if (*p == PACK_DELETEMEMBER_S)
	{
		printf("ȸ��Ż�� ����\n");
	}
	else if (*p == PACK_DELETEMEMBER_F)
	{
		printf("ȸ��Ż�� ����\n");
	}
}

void fun_NewMember()
{
	printf("[ȸ������ ���� �Է�] \n\n");
	char id[20], pw[20], name[20];

	printf("���̵� : ");			gets_s(id, sizeof(id));
	printf("�н����� : ");		gets_s(pw, sizeof(pw));
	printf("�̸� : ");			gets_s(name, sizeof(name));

	//������ ������ ��Ŷ�� ����!
	NEWMEMBER packet = pack_NewMember(id, pw, name);

	//������ ����
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("���� ����\n");
	}
	else
	{
		printf("���� ����\n");
	}
}

void fun_Login()
{
	printf("[�α��� ���� �Է�] \n\n");
	char id[20], pw[20];

	printf("���̵� : ");			gets_s(id, sizeof(id));
	printf("�н����� : ");		gets_s(pw, sizeof(pw));

	//������ ������ ��Ŷ�� ����!
	LOGIN packet = pack_Login(id, pw);

	//������ ����
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("���� ����\n");
	}
	else
	{
		printf("���� ����\n");
	}
}

void fun_Logout()
{
	printf("[�α׾ƿ� ���� �Է�] \n\n");
	char id[20];

	printf("���̵� : ");			gets_s(id, sizeof(id));

	//������ ������ ��Ŷ�� ����!
	LOGIN packet = pack_Logout(id);

	//������ ����
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("���� ����\n");
	}
	else
	{
		printf("���� ����\n");
	}
}

void fun_DeleteMember()
{
	printf("[ȸ��Ż�� ���� �Է�] \n\n");
	char id[20];

	printf("���̵� : ");			gets_s(id, sizeof(id));

	//������ ������ ��Ŷ�� ����!
	LOGIN packet = pack_DeleteMember(id);

	//������ ����
	if (wbnet_SendData((const char*)&packet, sizeof(packet)) == -1)
	{
		printf("���� ����\n");
	}
	else
	{
		printf("���� ����\n");
	}
}

void Run()
{
	while (true)
	{
		printf("--------------------------------------------------------------------\n");
		printf("[0] ���α׷����� [1] ȸ������ [2] �α��� [3] �α׾ƿ� [4] ȸ��Ż��\n");
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
	//---------------- �ʱ�ȭ ------------------------------
	if (wbnet_LibraryInit() == 0)
	{
		printf("���̺귯�� �ʱ�ȭ ����\n");
		return 0;
	}

	if (wbnet_CreateSocket() == 0)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	//---------------- ���� ------------------------------
	if (wbnet_Run(SERVER_PORT, SERVER_IP) == 0)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	Run();

	//---------------- ����ó�� ------------------------------
	wbnet_DeleteSocket();

	wbnet_LibraryExit();

	return 0;
}