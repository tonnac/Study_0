#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void GameRun();
void GameInit();
void GameRelease();

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
					LPWSTR lpCmdLine, int nCmdShow)
	// <w>WinMain (.. , .. ,LP<W>STR,..) 유니코드용
{
	WNDCLASSEX wc;							  // EX 확장, W 유니코드
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		  // 고정
	wc.lpfnWndProc = WndProc;				  // 윈도우프로시져 함수주소 등록
	wc.hInstance = hInst;					  // 인자로 받은 인스턴스 전달
	wc.lpszClassName = L"MyWindow";			  // 윈도우의 이름
	wc.hIcon = LoadIcon(hInst, IDI_SHIELD);   // 윈도우의 아이콘
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.hIconSm = LoadIcon(nullptr, IDI_HAND);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;


	if (RegisterClassEx(&wc) == false)	 // 확장이면 RegisterClass에도 <EX> 붙여줌
	{
		return 1;
	}
	// 윈도우 등록되면 생성
	HWND hWnd = CreateWindowEx(
		WS_EX_APPWINDOW, 
		L"MyWindow", 
		L"KGCA SAMPLE", 
		WS_OVERLAPPEDWINDOW,  // WS_POPUPWINDOW (타이틀바가 없어서 윈도우를 못움직임)
		0, // 시작지점 x좌표
		0, // 시작지점 y좌표
		800, // 창 넓이
		600, // 창 높이
		nullptr,
		nullptr,
		hInst,
		nullptr);
	if (hWnd == nullptr)
	{
		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);

	GameInit();
	//메세지 큐에서 메세지 1개 가져옴
	MSG msg; // WM_QUIT 이면 GetMessage false 리턴
	ZeroMemory(&msg, sizeof(MSG));

	// GetMessage(&msg, nullptr, 0, 0)  // PostQuitMessage를 받기위해 윈도우 핸들말고 nullptr을 넘긴다
	// 메세지 큐에서 메세지 1개 이상일 경우에 1개를 가져온다.
	// PeekMessage  게임에선 Get보단 Peek사용
	// 메세지 큐에서 메세지 있으면 메세지 반환, 없으면 false 반환

	while (true) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			// 화면에 무언가 뿌린다.(Draw);
			GameRun();
		}
	}
	GameRelease();
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			MessageBox(NULL, L"윈도우", L"윈도우생성", MB_ABORTRETRYIGNORE);
		}return 0;
		case WM_DESTROY:
		{
			PostQuitMessage(0);    // WM_QUIT --> Push
			//DestroyWindow(hWnd); // WM_DESTROY --> 메세지 큐에 푸시
		}return 0;
		case WM_LBUTTONDOWN:
		{
			DestroyWindow(hWnd);
		}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
void GameRun()
{
	// 지형, 오브젝트, 이펙트, UI
}
void GameInit()
{
	// 지형, 오브젝트, 이펙트, UI 초기화, 로딩
}
void GameRelease()
{
	// 지형, 오브젝트, 이펙트, UI 소멸
}