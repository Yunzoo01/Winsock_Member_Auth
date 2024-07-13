//wbnet.h

#pragma once

//라이브러리 초기화
int wbnet_LibraryInit();

//소켓생성 + 주소할당 + 망 연결
int wbnet_CreateListenSocket(int port);

//소켓 종료
void wbnet_DeleteListenSocket();

//라이브러리 해제
void wbnet_LibraryExit();


//[클라이언트 접속처리 + 스레드 생성] : 무한 반복
void wbnet_ServerRun();

//통신 스레드 함수
//wbnet_ServerRun에서 호출!
unsigned int __stdcall WorkThread(void* param);


//입출력 함수
int recvn(SOCKET s, char* buf, int len, int flags);
int wbsend(SOCKET s, char* buf, int len);
int wbrecive(SOCKET s, char* buf);
