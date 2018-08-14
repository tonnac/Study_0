#include "Core.h"
#include "EndScene.h"
#include <memory>
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
		return true;
	}
	bool Frame()
	{
		m_pGameScene->Frame();
		return true;
	}
	bool Render()
	{
		m_pGameScene->Render();
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