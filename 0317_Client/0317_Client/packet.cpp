//packet.cpp

#include "std.h"

NEWMEMBER pack_NewMember(const char* id, const char* pw, const char* name)
{
	NEWMEMBER pack;

	pack.flag = PACK_NEWMEMBER;
	strcpy_s(pack.id, sizeof(pack.id), id);
	strcpy_s(pack.pw, sizeof(pack.pw), pw);
	strcpy_s(pack.name, sizeof(pack.name), name);

	return pack;
}

LOGIN pack_Login(const char* id, const char* pw)
{
	LOGIN pack;

	pack.flag = PACK_LOGIN;
	strcpy_s(pack.id, sizeof(pack.id), id);
	strcpy_s(pack.pw, sizeof(pack.pw), pw);

	return pack;
}

LOGIN pack_Logout(const char* id)
{
	LOGIN pack;

	pack.flag = PACK_LOGOUT;
	strcpy_s(pack.id, sizeof(pack.id), id);

	return pack;
}

LOGIN pack_DeleteMember(const char* id)
{
	LOGIN pack;

	pack.flag = PACK_DELETEMEMBER;
	strcpy_s(pack.id, sizeof(pack.id), id);

	return pack;
}


