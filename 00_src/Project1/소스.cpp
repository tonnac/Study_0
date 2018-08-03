#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	LPWSTR lpCmdLine, int nCmdShow)
	// <w>WinMain (.. , .. ,LP<W>STR,..) 유니코드용
{
	WNDCLASSEX wc;							  // EX 확장, W 유니코드
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		  // 고정
	wc.lpfnWndProc = WndProc;				  // 윈도우프로시져 함수주소 등록
	wc.hInstance = hInst;					  // 인자로 받은 인스턴스 전달
	wc.lpszClassName = L"MyWindow";			  // 윈도우의 이름
	wc.hIcon = LoadIcon(hInst, IDI_QUESTION); //윈도우의 아이콘
	wc.hCursor = LoadIcon(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//int         cbClsExtra;
	//int         cbWndExtra;

	if (RegisterClassEx(&wc) == false)	 // 확장이면 RegisterClass에도 <EX> 붙여줌
	{
		return 1;
	}

	// 윈도우 등록되면 생성
	HWND hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"MyWindow",
		L"KGCA SAMPLE",
		WS_OVERLAPPEDWINDOW,
		0, // 시작지점 x좌표
		0, // 시작지점 y좌표
		800, // 창 넓이
		600, // 창 높이
		NULL,
		NULL,
		hInst,
		NULL);
	if (hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);

	//메세지 큐에서 메세지 1개 가져옴
	MSG msg; // WM_QUIT 이면 GetMessage false 리턴
	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		int kkk = 0;
	}return 0;
	case WM_DESTROY:
	{
		int kkk = 0;
		PostQuitMessage(0);    // WM_QUIT --> Push
							   //DestroyWindow(hWnd); // WM_DESTROY --> 메세지 큐에 푸시
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}