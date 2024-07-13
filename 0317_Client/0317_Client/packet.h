//packet.h

#pragma once

#define PACK_NEWMEMBER      1               //NEWMEMBER����ü(ID,PW,NAME����)-> idüũ ����/����
#define PACK_LOGIN          2               //LOGIN����ü (ID, PW����) -> id/pwüũ ����(�����Ͱ���)/����
#define PACK_DELETEMEMBER   3               //LOGIN����ü (ID�� ����) -> �ش�ID�� �ִٸ� ���� (����/����)
#define PACK_LOGOUT         4               //LOGIN����ü (ID�� ����) -> �ش�ID Ȯ��(������ ����) / 

//���� --> Ŭ���̾�Ʈ : 
//Ŭ���̾�Ʈ�� ���� ��Ŷ�� flag���� ����/���� ���η� �����ؼ� ����!
#define PACK_NEWMEMBER_S        10          //NEWMEMBER����ü
#define PACK_NEWMEMBER_F        11          //NEWMEMBER����ü
#define PACK_LOGIN_S            12          //LOGIN����ü
#define PACK_LOGIN_F            13          //LOGIN����ü
#define PACK_LOGOUT_S           14          //LOGIN����ü
#define PACK_LOGOUT_F           15          //LOGIN����ü
#define PACK_DELETEMEMBER_S     16          //LOGIN����ü
#define PACK_DELETEMEMBER_F     17          //LOGIN����ü


struct NEWMEMBER
{
    int flag;
    char id[20];
    char pw[30];
    char name[20];
};

struct LOGIN 
{
    int flag;
    char id[10];
    char pw[10];
};

struct MESSAGE 
{
    int flag;
    char id[10];
    char str[50];
};

NEWMEMBER pack_NewMember(const char* id, const char* pw, const char* name);
LOGIN pack_Login(const char* id, const char* pw);
LOGIN pack_Logout(const char* id);
LOGIN pack_DeleteMember(const char* id);