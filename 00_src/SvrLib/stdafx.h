// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>
#include <Windows.h>
#include <vector>
#include <list>
#include <map>
#include <tchar.h>
#include <algorithm>

#pragma comment(lib, "SvrLib")
#pragma comment(lib, "ws2_32")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define BUF_SIZE 2048

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
