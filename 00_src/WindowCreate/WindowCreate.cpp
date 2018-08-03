#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void GameRun()
{
	//
}

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE prev, LPWSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	ZeroMemory(&wndclass, sizeof(WNDCLASSEX));
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hinst;
	wndclass.hIcon = LoadIcon(nullptr, IDI_SHIELD);
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));
	wndclass.hIconSm = LoadIcon(nullptr, IDI_SHIELD);

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(nullptr, TEXT("This Program requiers Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		L"The Hello Program", 
		WS_OVERLAPPEDWINDOW, 
		0,
		0,
		800,
		600,
		nullptr,
		nullptr, 
		hinst, 
		nullptr);
	
	if (hwnd == nullptr)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	ZeroMemory(&msg, sizeof(MSG));
	while(true)
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
			GameRun();
		}
	}


	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (msg)
	{
	case WM_CREATE:
		//PlaySound(L"hellowin.wav", nullptr, SND_FILENAME | SND_ASYNC);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);

		DrawText(hdc, L"Hello, WindowS", -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}