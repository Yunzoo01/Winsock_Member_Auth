//std.h
#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <process.h>		//_beginthread()
#include <conio.h>

#include "packet.h"
#include "wbnet.h"
