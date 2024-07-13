//wbnet.h
#pragma once

//���̺귯�� �ʱ�ȭ
int wbnet_LibraryInit();

//���� ����
int wbnet_CreateSocket();

//���� ���� + recvthread ����
int wbnet_Run(int port, const char* ip);

//���� ����
void wbnet_DeleteSocket();

//���̺귯�� ����
void wbnet_LibraryExit();

//������ ���� - wbnet_Run���� ȣ��
unsigned int __stdcall ReciveThread(void* param);

//������ ����
int wbnet_SendData(const char* msg, int size);

int recvn(SOCKET s, char* buf, int len, int flags);
int wbsend(SOCKET s, char* buf, int len);
int wbrecive(SOCKET s, char* buf);