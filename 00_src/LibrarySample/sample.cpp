#include "Core.h"

struct KPoint
{
	float x, y;
};

class KSample : public KCore
{
	KPoint m_pos;
	Bitmap m_bBitmap;
public:
	bool Init()
	{
		m_bBitmap.Init();
		m_bBitmap.LoadFile(L"../../01_data/Number.bmp");
		m_pos.x = m_pos.y = 80.0f;
		return true;
	}
	bool Frame()
	{
		if (I_KInput.getKey('A'))
		{
			m_pos.x += (-1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('D'))
		{
			m_pos.x += (1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('W'))
		{
			m_pos.y += (-1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getKey('S'))
		{
			m_pos.y += (1 * g_fSecPerFrame * 200.0f);
		}
		if (I_KInput.getMouse(VK_MBUTTON) == KEY_PUSH)
		{
			MessageBox(nullptr, L"KEY_PUSH", L"LBUTTON", MB_OK);
		}
		m_bBitmap.Frame();
		return true;
	}
	bool Render()
	{
		static DWORD frame = 0;
		HDC MemDC = m_bBitmap.getMemDC();
		//	Sleep(10);
		BitBlt(g_hOffScreenDC, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 47, 48, MemDC, 1 + (frame * 48), 0, SRCCOPY);
		frame = (++frame) % 12;
		return m_bBitmap.Render();
	}
	bool Release()
	{
		return m_bBitmap.Release();
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst);
	wd.Run();
	return 0;
}