//wbnet.h
#pragma once

//라이브러리 초기화
int wbnet_LibraryInit();

//소켓 생성
int wbnet_CreateSocket();

//서버 접속 + recvthread 생성
int wbnet_Run(int port, const char* ip);

//소켓 종료
void wbnet_DeleteSocket();

//라이브러리 해제
void wbnet_LibraryExit();

//데이터 수신 - wbnet_Run에서 호출
unsigned int __stdcall ReciveThread(void* param);

//데이터 전송
int wbnet_SendData(const char* msg, int size);

int recvn(SOCKET s, char* buf, int len, int flags);
int wbsend(SOCKET s, char* buf, int len);
int wbrecive(SOCKET s, char* buf);