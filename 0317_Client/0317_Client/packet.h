//packet.h

#pragma once

#define PACK_NEWMEMBER      1               //NEWMEMBER구조체(ID,PW,NAME전달)-> id체크 저장/실패
#define PACK_LOGIN          2               //LOGIN구조체 (ID, PW전달) -> id/pw체크 성공(데이터갱신)/실패
#define PACK_DELETEMEMBER   3               //LOGIN구조체 (ID만 전달) -> 해당ID가 있다면 삭제 (성공/실패)
#define PACK_LOGOUT         4               //LOGIN구조체 (ID만 전달) -> 해당ID 확인(데이터 갱신) / 

//서버 --> 클라이언트 : 
//클라이언트가 보낸 패킷의 flag값만 성공/실패 여부로 변경해서 전달!
#define PACK_NEWMEMBER_S        10          //NEWMEMBER구조체
#define PACK_NEWMEMBER_F        11          //NEWMEMBER구조체
#define PACK_LOGIN_S            12          //LOGIN구조체
#define PACK_LOGIN_F            13          //LOGIN구조체
#define PACK_LOGOUT_S           14          //LOGIN구조체
#define PACK_LOGOUT_F           15          //LOGIN구조체
#define PACK_DELETEMEMBER_S     16          //LOGIN구조체
#define PACK_DELETEMEMBER_F     17          //LOGIN구조체


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