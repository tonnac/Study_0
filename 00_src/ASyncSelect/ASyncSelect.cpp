#include "Sample.h"
#include <algorithm>
#include "ASyncSelect.h"
#define WM_KGCA (WM_USER+0)

HWND g_hWnd = nullptr;
SOCKET User::g_sock = 0;

int RecvData(const User& user)
{
	bool bConnect = true;
	char buffer[BUF_SIZE] = { 0, };
	SOCKET sock = user.sock;
	int iRet = 0;
	int iRecvByte = 0;
	iRet = recv(sock, &buffer[iRecvByte], sizeof(char) * PACKET_HEADER_SIZE - iRecvByte, 0);
	if (iRet == 0)
	{
		return 0;
	}
	else if (iRet == SOCKET_ERROR)
	{
		return -1;
	}
	//else if (iRet != WSAEWOULDBLOCK)
	//{
	//	PostMessage(g_hWnd, WM_KGCA, sock, FD_READ);
	//}
	iRecvByte += iRet;
	if (iRecvByte == PACKET_HEADER_SIZE)
	{
		UPACKET packet;
		ZeroMemory(&packet, sizeof(packet));
		memcpy(&packet.ph.len, buffer, sizeof(char) * PACKET_HEADER_SIZE);
		int rByte = 0;
		do
		{
			int iRecvByte2 = recv(sock, (char*)&packet.msg[rByte], sizeof(char) * packet.ph.len - rByte, 0);
			if (iRecvByte2 == 0 || iRecvByte2 == SOCKET_ERROR)
			{
				ErrorMsg();
				bConnect = false;
				break;
			}
			rByte += iRecvByte2;
		} while (packet.ph.len > rByte);

		switch (packet.ph.type)
		{
		case PACKET_CHAT_MSG:
		{
			BroadCasting(packet.msg);
			printf("패킷완성%s", packet.msg);
		}break;
		}
	}
	if (bConnect == false) return -1;
	return 1;
}


LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_KGCA:
		{
			if (WSAGETSELECTERROR(lParam))
			{
				closesocket(wParam);
			}
			else
			{
				switch (WSAGETSELECTEVENT(lParam))
				{
					case FD_ACCEPT:
					{
						User addUser;
						addUser.sock = accept(wParam, (sockaddr*)&addUser.Addr, &addUser.addrLen);
						char ip[512] = { 0, };
						printf("%s, %d 접속\n", inet_ntop(AF_INET, &addUser.Addr.sin_addr, ip, sizeof(ip)), ntohs(addUser.Addr.sin_port));
						if (addUser.sock == INVALID_SOCKET)
						{
							break;
						}
						AddUser(addUser);
						int iRet = WSAAsyncSelect(addUser.sock, hWnd, WM_KGCA, FD_READ | FD_CLOSE | FD_WRITE);
						if (iRet == SOCKET_ERROR)
						{
							return -1;
						}
					}break;
					case FD_READ:
					{
						User::g_sock = wParam;
						User_Iter iter = std::find_if(g_allUser.begin(), g_allUser.end(), User());
						if (RecvData(*iter) <= 0)
						{
							char ip[512] = { 0, };
							printf("%s, %d 접종1\n", inet_ntop(AF_INET, &iter->Addr.sin_addr, ip, sizeof(ip)), ntohs(iter->Addr.sin_port));
							iter = g_allUser.erase(iter);
						}
					}break;
					case FD_WRITE:
					{
						// 받은 패킷을 넣어두는 곳이 없다.
						// 패킷 풀 
					}break;
					case FD_CLOSE:
					{
						PostMessage(hWnd, WM_KGCA, wParam, FD_READ);
					}break;
					default:
						break;
				}
			}
		}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND MakeWindow()
{
	HWND hWnd;
	HINSTANCE hInstance = nullptr;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_SHIELD);
	wc.lpszMenuName = L"Window";
	wc.lpszClassName = L"MainWnd";
	wc.hIconSm = LoadIcon(nullptr, IDI_SHIELD);

	if (!RegisterClassEx(&wc))
	{
		return nullptr;
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW,
		0, 0,0, 0, 0, 0, hInstance, 0);
	return hWnd;
}

int main(void)
{
	const u_short port = 10000;
	if (BeginWinSock() == false)
	{
		return -1;
	}

	SOCKET Listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	HWND hWnd = g_hWnd = MakeWindow();

	int iRet = bind(Listensock, (sockaddr*)&addr, sizeof(addr));
	if (iRet != 0)
	{
		return -1;
	}

	iRet = listen(Listensock, SOMAXCONN);
	if (iRet != 0)
	{
		return -1;
	}

	char ip[INET_ADDRSTRLEN] = { 0, };

	iRet = WSAAsyncSelect(Listensock, hWnd, WM_KGCA, FD_ACCEPT);
	if (iRet == SOCKET_ERROR)
	{
		return -1;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (iRet = GetMessage(&msg, nullptr, 0, 0))
	{
		if (iRet == -1) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//bool bEnding = false;
	//while (bEnding == false)
	//{
	//	User_Iter iter = g_allUser.begin();
	//	while (iter != g_allUser.end())
	//	{
	//		FD_SET(iter->sock, &rSet);
	//		FD_SET(iter->sock, &wSet);
	//		FD_SET(iter->sock, &eSet);
	//		++iter;
	//	}
	//	timeval time;
	//	time.tv_sec = 1;
	//	time.tv_usec = 0;
	//	int iValue = select(0, &rSet, &wSet, &eSet, &time);
	//	if (iValue == SOCKET_ERROR) break;
	//	if (iValue == 0) {} // timeout
	//	else
	//	{
	//		if (FD_ISSET(Listensock, &rSet))
	//		{
	//			User addUser;
	//			addUser.sock = accept(Listensock, (sockaddr*)&addUser.Addr, &addUser.addrLen);
	//			char ip[512] = { 0, };
	//			printf("%s, %d 접속\n", inet_ntop(AF_INET, &addUser.Addr.sin_addr, ip, sizeof(ip)), ntohs(addUser.Addr.sin_port));
	//			if (addUser.sock == INVALID_SOCKET)
	//			{
	//				bEnding = true;
	//				break;
	//			}
	//			AddUser(addUser);
	//		}
	//		iter = g_allUser.begin();
	//		while (iter != g_allUser.end())
	//		{
	//			User user = (User)*iter;
	//			SOCKET sock = user.sock;
	//			if (FD_ISSET(iter->sock, &rSet))
	//			{
	//				if (RecvData(user) <= 0)
	//				{
	//					char ip[512] = { 0, };
	//					printf("%s, %d 접종1\n", inet_ntop(AF_INET, &user.Addr.sin_addr, ip, sizeof(ip)), ntohs(user.Addr.sin_port));
	//					iter = g_allUser.erase(iter);
	//					continue;
	//				}
	//			}
	//			if (FD_ISSET(sock, &wSet))
	//			{
	//				int kkk = 0;
	//			}
	//			if (FD_ISSET(sock, &eSet))
	//			{
	//				char ip[512] = { 0, };
	//				printf("%s, %d 접종2\n", inet_ntop(AF_INET, &user.Addr.sin_addr, ip, sizeof(ip)), ntohs(user.Addr.sin_port));
	//				closesocket(iter->sock);
	//				iter = g_allUser.erase(iter);
	//				continue;
	//			}
	//			++iter;
	//		}
	//	}
	//}

	//SOCKET client;
	//SOCKADDR_IN clientaddr;
	//int AddrLen = sizeof(clientaddr);
	//client = accept(Listensock, (sockaddr*)&clientaddr, &AddrLen);
	//if (client != SOCKET_ERROR)
	//{
	//	User user;
	//	user.sock = client;
	//	user.Addr = clientaddr;
	//	AddUser(user);
	//	printf("%s, %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, ip, sizeof(ip)), ntohs(clientaddr.sin_port));
	//	DWORD threadID;
	//	HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)g_allUser[user.sock], 0, &threadID);
	//}
	closesocket(Listensock);
	if (EndWinSock() == false)
	{
		return -1;
	}
	return 0;
}