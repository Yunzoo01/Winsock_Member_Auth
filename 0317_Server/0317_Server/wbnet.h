//wbnet.h

#pragma once

//���̺귯�� �ʱ�ȭ
int wbnet_LibraryInit();

//���ϻ��� + �ּ��Ҵ� + �� ����
int wbnet_CreateListenSocket(int port);

//���� ����
void wbnet_DeleteListenSocket();

//���̺귯�� ����
void wbnet_LibraryExit();


//[Ŭ���̾�Ʈ ����ó�� + ������ ����] : ���� �ݺ�
void wbnet_ServerRun();

//��� ������ �Լ�
//wbnet_ServerRun���� ȣ��!
unsigned int __stdcall WorkThread(void* param);


//����� �Լ�
int recvn(SOCKET s, char* buf, int len, int flags);
int wbsend(SOCKET s, char* buf, int len);
int wbrecive(SOCKET s, char* buf);
