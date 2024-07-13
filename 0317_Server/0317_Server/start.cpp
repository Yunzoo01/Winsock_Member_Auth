//start.cpp

#include "std.h"

#define SERVER_PORT 9000

vector< NEWMEMBER > g_members;  //flag(�α��ο���), id, pw, name

//�ߺ��� ������ true��ȯ
bool isIdUniqCheck(const char* id)
{
	for (int i = 0; i < (int)g_members.size(); i++)
	{
		NEWMEMBER mem = g_members[i];
		if (strcmp(mem.id , id) == 0)
			return true;
	}
	return false;
}

void fun_RecvData(char* msg)
{
	system("cls");

	int* p = (int*)msg;
	if (*p == PACK_NEWMEMBER)
	{
		NEWMEMBER* p = (NEWMEMBER*)msg;
		if (isIdUniqCheck(p->id) == true)
		{
			pack_NewMemberAck(msg, false);
		}
		else
		{
			NEWMEMBER mem;
			mem.flag = 0;
			strcpy_s(mem.id, sizeof(mem.id), p->id);
			strcpy_s(mem.pw, sizeof(mem.pw), p->pw);
			strcpy_s(mem.name, sizeof(mem.name), p->name);

			g_members.push_back(mem);
			pack_NewMemberAck(msg, true);
		}		
	}
	else if (*p == PACK_LOGIN)
	{
		LOGIN* p = (LOGIN*)msg;

		for (int i = 0; i < (int)g_members.size(); i++)
		{
			NEWMEMBER mem = g_members[i];
			if (strcmp(mem.id, p->id) == 0 && strcmp(mem.pw, p->pw) == 0)
			{
				g_members[i].flag = 1;
				pack_LoginAck(msg, true);
				break;
			}
			else
			{
				pack_LoginAck(msg, false);
				break;
			}
		}
	}
	else if (*p == PACK_LOGOUT)
	{
		LOGIN* p = (LOGIN*)msg;

		for (int i = 0; i < (int)g_members.size(); i++)
		{
			NEWMEMBER mem = g_members[i];
			if (strcmp(mem.id, p->id) == 0)
			{
				g_members[i].flag = 0;
				pack_LogoutAck(msg, true);
				break;
			}
			else
			{
				pack_LogoutAck(msg, false);
			}
		}
	}
	else if (*p == PACK_DELETEMEMBER)
	{
		LOGIN* p = (LOGIN*)msg;

		for (int i = 0; i < (int)g_members.size(); i++)
		{
			NEWMEMBER mem = g_members[i];
			if (strcmp(mem.id, p->id) == 0)
			{
				g_members.erase(g_members.begin() + i);
				pack_DeleteMemberAck(msg, true);
				break;
			}
			else
			{
				pack_DeleteMemberAck(msg, false);
			}
		}
	}

	//��ü ���
	for (int i = 0; i < (int)g_members.size(); i++)
	{
		NEWMEMBER mem = g_members[i];

		printf("[%d] %s\t%s\t%s\n", mem.flag, mem.id, mem.pw, mem.name);
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

	if (wbnet_CreateListenSocket(SERVER_PORT) == -1)
		return 0;
	
	//----------------- ���� ----------------------------------
	wbnet_ServerRun();

	//----------------- ���� ----------------------------------
	wbnet_DeleteListenSocket();
	
	wbnet_LibraryExit();

	return 0;
}