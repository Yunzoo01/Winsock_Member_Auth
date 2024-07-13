//packet.cpp

#include "std.h"

void pack_NewMemberAck(char* msg, bool b)
{
	NEWMEMBER* p = (NEWMEMBER*)msg;
	if( b == true)
		p->flag = PACK_NEWMEMBER_S;
	else
		p->flag = PACK_NEWMEMBER_F;
}

void pack_LoginAck(char* msg, bool b)
{
	NEWMEMBER* p = (NEWMEMBER*)msg;
	if (b == true)
		p->flag = PACK_LOGIN_S;
	else
		p->flag = PACK_LOGIN_F;
}

void pack_LogoutAck(char* msg, bool b)
{
	NEWMEMBER* p = (NEWMEMBER*)msg;
	if (b == true)
		p->flag = PACK_LOGOUT_S;
	else
		p->flag = PACK_LOGOUT_F;
}

void pack_DeleteMemberAck(char* msg, bool b)
{
	NEWMEMBER* p = (NEWMEMBER*)msg;
	if (b == true)
		p->flag = PACK_DELETEMEMBER_S;
	else
		p->flag = PACK_DELETEMEMBER_F;
}

