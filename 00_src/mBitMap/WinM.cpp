#include "Core.h"

struct KPOINT
{
	float x, y;
};


class Simple : public Core
{
private:
	KPOINT m_pos;
	Bitmap m_bitmap;
public:
	bool Init()
	{
		m_pos.x = 100;
		m_pos.y = 100;
		m_bitmap.LoadFile(L"bitmap1.bmp");
		return true;
	}
	bool Frame()
	{
		if (I_input.getKey('A'))
		{
			m_pos.x += (-1 * g_fSecPerFrame * 100.0f);
		}
		if (I_input.getKey('D'))
		{
			m_pos.x += (1 * g_fSecPerFrame * 100.0f);
		}
		if (I_input.getKey('W'))
		{
			m_pos.y += (-1 * g_fSecPerFrame * 100.0f);
		}
		if (I_input.getKey('S'))
		{
			m_pos.y += (1 * g_fSecPerFrame * 100.0f);
		}
		return true;
	}
	bool Render()
	{
		BitBlt(m_hOffScreenDC, (int)m_pos.x, (int)m_pos.y, 200, 200, m_bitmap.m_hMemDC, 100, 100, SRCCOPY);
		return true;
	}
	bool Release()
	{
		return true;
	}
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE prev, LPWSTR szCmdLine, int cmd)
{
	Simple wd;
	wd.setWindow(hinst);
	wd.Run();

	return 0;
}