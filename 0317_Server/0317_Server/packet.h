//packet.h
#pragma once

//클라이언트 --> 서버
#define PACK_NEWMEMBER      1
#define PACK_LOGIN          2
#define PACK_DELETEMEMBER   3              
#define PACK_LOGOUT         4  

//서버 --> 클라이언트
#define PACK_NEWMEMBER_S        10
#define PACK_NEWMEMBER_F        11
#define PACK_LOGIN_S            12          
#define PACK_LOGIN_F            13          
#define PACK_LOGOUT_S           14          
#define PACK_LOGOUT_F           15          
#define PACK_DELETEMEMBER_S     16         
#define PACK_DELETEMEMBER_F     17         

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

//수신한 NEWMEMBER 구조체 타입의 flag만 변경해서 전달!
void pack_NewMemberAck(char* msg, bool b);
void pack_LoginAck(char* msg, bool b);
void pack_LogoutAck(char* msg, bool b);
void pack_DeleteMemberAck(char* msg, bool b);
