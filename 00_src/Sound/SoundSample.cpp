#include "Core.h"
#include "EndScene.h"
#include <memory>
#include "Sound.h"

using SCENE = std::shared_ptr<Scene>;

class KSample : public KCore
{
	SCENE			m_pGameScene;
//	Sound			_Sound;
public:
	bool Init()
	{
		m_pGameScene = std::make_shared<SceneGame>();
		m_pGameScene->Init();
		Sound::GetInstance().Init();
		Sound::GetInstance().Load("../../sound/00_Menu.mp3",true);
		return true;
	}
	bool Frame()
	{
		Sound::GetInstance().Frame();
		if (I_KInput.getKey('1') == KEY_PUSH)
		{
			Sound::GetInstance().Play(3);
		}
		if (I_KInput.getKey('2') == KEY_PUSH)
		{
			Sound::GetInstance().Pause(3);
		}
		if (I_KInput.getKey('3') == KEY_PUSH)
		{
			Sound::GetInstance().Stop(3);
		}
		if (I_KInput.getKey(VK_INSERT) == KEY_HOLD)
		{
			Sound::GetInstance().Volume(0, g_fSecPerFrame*1.0f, true);
		}
		if (I_KInput.getKey(VK_DELETE) == KEY_HOLD)
		{
			Sound::GetInstance().Volume(0, g_fSecPerFrame*1.0f, false);
		}
		m_pGameScene->Frame();
		return true;
	}
	bool Render()
	{
		m_pGameScene->Render();
		Sound::GetInstance().Render();
		return true;
	}
	bool Release()
	{
		m_pGameScene->Release();
		return true;
	}
private:
};



int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPWSTR szCmdLine, int nCmdShow)
{
	KSample wd;
	wd.SetWindow(hInst, 800, 600);
	wd.Run();
	return 0;
}