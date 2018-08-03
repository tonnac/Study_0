#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void GameRun();
void GameInit();
void GameRelease();

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
					LPWSTR lpCmdLine, int nCmdShow)
	// <w>WinMain (.. , .. ,LP<W>STR,..) �����ڵ��
{
	WNDCLASSEX wc;							  // EX Ȯ��, W �����ڵ�
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;		  // ����
	wc.lpfnWndProc = WndProc;				  // ���������ν��� �Լ��ּ� ���
	wc.hInstance = hInst;					  // ���ڷ� ���� �ν��Ͻ� ����
	wc.lpszClassName = L"MyWindow";			  // �������� �̸�
	wc.hIcon = LoadIcon(hInst, IDI_SHIELD);   // �������� ������
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.hIconSm = LoadIcon(nullptr, IDI_HAND);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;


	if (RegisterClassEx(&wc) == false)	 // Ȯ���̸� RegisterClass���� <EX> �ٿ���
	{
		return 1;
	}
	// ������ ��ϵǸ� ����
	HWND hWnd = CreateWindowEx(
		WS_EX_APPWINDOW, 
		L"MyWindow", 
		L"KGCA SAMPLE", 
		WS_OVERLAPPEDWINDOW,  // WS_POPUPWINDOW (Ÿ��Ʋ�ٰ� ��� �����츦 ��������)
		0, // �������� x��ǥ
		0, // �������� y��ǥ
		800, // â ����
		600, // â ����
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
	//�޼��� ť���� �޼��� 1�� ������
	MSG msg; // WM_QUIT �̸� GetMessage false ����
	ZeroMemory(&msg, sizeof(MSG));

	// GetMessage(&msg, nullptr, 0, 0)  // PostQuitMessage�� �ޱ����� ������ �ڵ鸻�� nullptr�� �ѱ��
	// �޼��� ť���� �޼��� 1�� �̻��� ��쿡 1���� �����´�.
	// PeekMessage  ���ӿ��� Get���� Peek���
	// �޼��� ť���� �޼��� ������ �޼��� ��ȯ, ������ false ��ȯ

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
			// ȭ�鿡 ���� �Ѹ���.(Draw);
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
			MessageBox(NULL, L"������", L"���������", MB_ABORTRETRYIGNORE);
		}return 0;
		case WM_DESTROY:
		{
			PostQuitMessage(0);    // WM_QUIT --> Push
			//DestroyWindow(hWnd); // WM_DESTROY --> �޼��� ť�� Ǫ��
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
	// ����, ������Ʈ, ����Ʈ, UI
}
void GameInit()
{
	// ����, ������Ʈ, ����Ʈ, UI �ʱ�ȭ, �ε�
}
void GameRelease()
{
	// ����, ������Ʈ, ����Ʈ, UI �Ҹ�
}