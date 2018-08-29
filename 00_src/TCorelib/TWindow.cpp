#include "TWindow.h"
TWindow*	g_pWindow = 0;
HWND		g_hWnd = NULL;
HINSTANCE	g_hInstance = NULL;
RECT		g_rtClient;
bool		g_bActiveApp = false;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	assert(g_pWindow!=NULL);
	LRESULT ret;	
	if (ret = g_pWindow->MsgProc(hWnd, msg, wParam, lParam))
	{
		return ret;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT TWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_ACTIVATEAPP:
			g_bActiveApp = (BOOL)wParam; //wParam에 TRUE가 들어오면 활성화.
		break;
		case WM_CREATE:
		{
			//MessageBox(NULL, L"윈도우가 떴다.", L"윈도우생성", MB_OK);
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);// WM_QUIT--> PUSH			
		}return 0;
	}
	return 0;
}
void TWindow::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}
bool TWindow::SetWindow(HINSTANCE	hInst,
	UINT iWidth, UINT iHeight)
{
	m_hInstance = hInst;
	g_hInstance = hInst;
	// 윈도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = L"MyWindow";	
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (RegisterClassEx(&wc) == FALSE)
	{
		return false;
	}
	// 클라이언트 영역 수정
	RECT rt = { 0,0,iWidth, iHeight };
	AdjustWindowRect(&rt, m_dwStyle, FALSE);
	//// 윈도우 생성( 등록된 클래스를 사용해서 )
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"MyWindow", L"Win",
		m_dwStyle,
		0, 0, 
		rt.right-rt.left, 
		rt.bottom - rt.top,
		NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL)
	{
		return false;
	}
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	
	CenterWindow();

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
void TWindow::Set(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}
void TWindow::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHegiht = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHegiht - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtWindow.right, m_rtWindow.bottom, true);
}
bool TWindow::Run()
{
	if (!GameInit()) return false;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
			MsgEvent(msg);
		}
		else
		{
			GameRun();
			Sleep(1);
		}
	}	
	return GameRelease();
}
bool TWindow::GameInit()
{
	return true;
}
bool TWindow::GameRun() {
	return true;
}
bool TWindow::GameRelease() {
	return true;
}
TWindow::TWindow()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	g_pWindow = this;
}


TWindow::~TWindow()
{
}
