#include "Core.h"


struct KPOINT
{
	float x, y;
};

class Simple : public Core
{
	Bitmap m_Bitmap;
	KPOINT m_pos;
public:
	bool Init()
	{
		m_pos.x = 100;
		m_pos.y = 100;
		m_Bitmap.Load(L"bitmap1.bmp");
		return true;
	}
	bool Frame()
	{
		if (I_input.getKey('W'))
		{
			m_pos.y += (-1 * g_fSecPerFrame)*300.f;
		}
		if (I_input.getKey('S'))
		{
			m_pos.y += (1 * g_fSecPerFrame)*300.f;
		}
		if (I_input.getKey('A'))
		{
			m_pos.x += (-1 * g_fSecPerFrame)*300.f;
		}
		if (I_input.getKey('D'))
		{
			m_pos.x += (1 * g_fSecPerFrame)*300.f;
		}
		return true;
	}
	bool Render()
	{
		BitBlt(m_hOffScreenDC, 
			static_cast<int>(m_pos.x), 
			static_cast<int>(m_pos.y), 
			68, 
			79,
			m_Bitmap.m_hMemDC, 
			46, 
			62, 
			SRCCOPY);
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