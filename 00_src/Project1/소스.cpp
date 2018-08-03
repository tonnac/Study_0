#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	LPWSTR lpCmdLine, int nCmdShow)
	// <w>WinMain (.. , .. ,LP<W>STR,..) �����ڵ��
{
	WNDCLASSEX wc;							  // EX Ȯ��, W �����ڵ�
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		  // ����
	wc.lpfnWndProc = WndProc;				  // ���������ν��� �Լ��ּ� ���
	wc.hInstance = hInst;					  // ���ڷ� ���� �ν��Ͻ� ����
	wc.lpszClassName = L"MyWindow";			  // �������� �̸�
	wc.hIcon = LoadIcon(hInst, IDI_QUESTION); //�������� ������
	wc.hCursor = LoadIcon(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(NULL, IDI_HAND);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//int         cbClsExtra;
	//int         cbWndExtra;

	if (RegisterClassEx(&wc) == false)	 // Ȯ���̸� RegisterClass���� <EX> �ٿ���
	{
		return 1;
	}

	// ������ ��ϵǸ� ����
	HWND hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"MyWindow",
		L"KGCA SAMPLE",
		WS_OVERLAPPEDWINDOW,
		0, // �������� x��ǥ
		0, // �������� y��ǥ
		800, // â ����
		600, // â ����
		NULL,
		NULL,
		hInst,
		NULL);
	if (hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);

	//�޼��� ť���� �޼��� 1�� ������
	MSG msg; // WM_QUIT �̸� GetMessage false ����
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
							   //DestroyWindow(hWnd); // WM_DESTROY --> �޼��� ť�� Ǫ��
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}