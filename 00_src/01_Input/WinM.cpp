#include "Core.h"

class Simple : public Core
{
private:
public:
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
		if (I_input.getKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"PUSH", L"LEFT", MB_OK);
		}
		if (I_input.getKey(VK_LEFT) == KEYSTATE::KEY_HOLD)
		{
			MessageBox(nullptr, L"HOLD", L"LEFT", MB_OK);
		}
		if (I_input.m_dwMouseState[1] == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"PUSH", L"LBUTTON", MB_OK);
		}
		if (I_input.m_dwMouseState[2] == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"PUSH", L"RBUTTON", MB_OK);
		}
		if (I_input.m_dwMouseState[0] == KEYSTATE::KEY_PUSH)
		{
			MessageBox(nullptr, L"PUSH", L"MBUTTON", MB_OK);
		}
		bool bCombo = (I_input.getKey(VK_LCONTROL) == KEYSTATE::KEY_HOLD && I_input.getKey(VK_LBUTTON) == KEYSTATE::KEY_PUSH);
		if (bCombo)
		{
			MessageBox(nullptr, L"PUSH", L"COMBO", MB_OK);
		}
		return true;
	}
	bool Render()
	{
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