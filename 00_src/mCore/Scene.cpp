#include "Scene.h"

Scene::Scene() : m_bNextSceneStart(false)
{}
bool Scene::inverseSet()
{
	return true;
}
bool Scene::getNextScene()
{
	return m_bNextSceneStart;
}
void * Scene::operator new(size_t sz, const char* FileName, int iLine)
{
	std::string ad = FileName;
	MEMINFO mem;
	void* pfs = new char[sz];
	mem.addr = pfs;
	mem.filename = ad.substr(ad.find_last_of('\\') + 1, ad.length() - (ad.find_last_of(".cpp") + 4));
	mem.line = iLine;
	mem.dwAllocateTime = timeGetTime();
	MemoryMap.insert(std::make_pair(pfs, mem));
	++::g_iNewCount;
	return pfs;
}
void Scene::operator delete(void * p)
{
	std::map<void*, MEMINFO>::iterator it;
	it = MemoryMap.find(p);
	MemoryMap.erase(it);
	--::g_iNewCount;
	delete p;
}

LobbyScene::LobbyScene() : isPress(false), m_nEffectVolume(10), m_nBGMVolume(10), isSoundBar(false)
{}										 
bool LobbyScene::Init()
{
	PosSet();
	for (int i = 0; i < 3; ++i)
	{
		m_bkmisc[i].LoadFile(L"TitleAnyKey", L"../../data/bmp/Misc.bmp");
		m_bkmisc[i].Init();
	}
	m_BKObject.LoadFile(L"MainMenu", L"../../data/bmp/Title_0.bmp");
	m_BKObject.Set(0, 0, 0, 0, g_rtClient.right, g_rtClient.bottom);
	m_BKObject.Init();
	m_BKObject.setFadeRender(0.0f,30.0f);
	m_state = LOBBYSTATE::DEFAULT;

	return true;
}
bool LobbyScene::Frame()
{
	BKState();
	if (m_BKObject.Frame() == false)
	{
		if (m_state == LOBBYSTATE::SELECT)
		{
			m_bNextSceneStart = true;
			return false;
		}
		m_state = LOBBYSTATE::START;
		m_BKObject.setRendering();
		m_miscIndex = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		m_bkmisc[i].Frame();
	}
	
	return true;
}
bool LobbyScene::Render()
{
	m_BKObject.Render();
	for (int i = 0; i < 3; ++i)
	{
		m_bkmisc[i].Render();
	}
	return true;
}
bool LobbyScene::Release()
{
	m_BKObject.Release();
	for (int i = 0; i < 3; ++i)
	{
		m_bkmisc[i].Release();
	}
	return true;
}
bool LobbyScene::BKState()
{
	switch (m_state)
	{
	case LOBBYSTATE::START:
		m_BKObject.Set(0, 0, 0, 0, 960, 720);
		m_bkmisc[0].Set(m_miscpos[m_miscIndex],m_miscrt[m_miscIndex]);
		if (S_Input.isPressAnyKey())
		{
			m_state = LOBBYSTATE::MAINMENU;
			m_miscIndex = 1;
		}
		break;
	case LOBBYSTATE::MAINMENU:
		if (m_miscIndex >= 2 && m_miscIndex <= 6)
		{
			if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex--;
			}
			if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex++;
			}
		}
		else if (m_miscIndex == 1)
		{
			if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex++;
			}
		}
		else
		{
			if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex--;
			}
		}
		if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
		{
			AKeyReact(m_miscIndex);
		}
		m_BKObject.Set(0, 0, 960, 0, 960, 720);
		m_bkmisc[0].Set(m_miscpos[m_miscIndex], m_miscrt[m_miscIndex]);
		break;
	case LOBBYSTATE::SETTING:
		if (m_miscIndex == 9)
		{
			if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex--;
			}
			if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH)
			{
				m_state = LOBBYSTATE::KEYSETTING;
				isSoundBar = false;
				m_miscIndex = 11;
			}
			if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
			{
				if (m_nBGMVolume > 0)
					m_nBGMVolume -= 1;
			}
			if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH)
			{
				if (m_nBGMVolume < 10)
					m_nBGMVolume += 1;
			}
		}
		else if (m_miscIndex == 8)
		{
			if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH)
			{
				m_miscIndex++;
			}
			if (S_Input.GetKey(VK_LEFT) == KEYSTATE::KEY_PUSH)
			{
				if(m_nEffectVolume > 0)
					m_nEffectVolume -= 1;
			}
			if (S_Input.GetKey(VK_RIGHT) == KEYSTATE::KEY_PUSH)
			{
				if(m_nEffectVolume < 10)
					m_nEffectVolume += 1;
			}
		}
		else
		{
			if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH)
			{
				m_state = LOBBYSTATE::KEYSETTING;
				isSoundBar = false;
				m_miscIndex = 11;
			}
			if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
			{
				AKeyReact(m_miscIndex);
			}
		}
		m_BKObject.Set(0, 0, 0, 720, 960, 720);
		m_bkmisc[0].Set(m_miscpos[m_miscIndex], m_miscrt[m_miscIndex]);
		if (!isSoundBar)
		{
			m_bkmisc[1].Set(741, 102, 390, 119, 0, 0);
			m_bkmisc[2].Set(741, 150, 390, 119, 0, 0);
		}
		else
		{
			m_bkmisc[1].Set(741, 102, 390, 119, 90 * m_nEffectVolume / 10.0f, 24);
			m_bkmisc[2].Set(741, 150, 390, 119, 90 * m_nBGMVolume / 10.0f, 24);
		}
		break;
	case LOBBYSTATE::KEYSETTING:
		m_BKObject.Set(0, 0, 960, 720, 960, 720);
		if (S_Input.GetKey(VK_UP) == KEYSTATE::KEY_PUSH)
		{
			m_state = LOBBYSTATE::SETTING;
			isSoundBar = true;
			m_miscIndex = 9;
		}
		if (S_Input.GetKey(VK_DOWN) == KEYSTATE::KEY_PUSH)
		{
			m_state = LOBBYSTATE::SETTING;
			isSoundBar = true;
			m_miscIndex = 10;
		}
		break;
	case LOBBYSTATE::SELECT:
		if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH)
		{
			m_BKObject.setFadeRender(255.0f,-200.0f);
			m_bkmisc[0].setFadeRender(255.0f, -200.0f);
			m_bkmisc[1].Set(0, 0, 0, 0, 0, 0);
		}
		if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH)
		{
			m_state = LOBBYSTATE::MAINMENU;
			m_bkmisc[1].Set(741, 102, 390, 119, 0, 0);
		}
	}


	return true;
}
void LobbyScene::PosSet()
{
	m_miscpos[0] = { 297,509 };
	m_miscpos[1] = { 3,0 };
	m_miscpos[2] = { 3,84 };
	m_miscpos[3] = { 3,168 };
	m_miscpos[4] = { 3,252 };
	m_miscpos[5] = { 3,336 };
	m_miscpos[6] = { 3,420 };
	m_miscpos[7] = { 3,504 };
	m_miscpos[8] = { 1,93 };
	m_miscpos[9] = { 1,141 };
	m_miscpos[10] = { 1,237 };

	m_miscrt[0] = { 3,119,381,36 };
	m_miscrt[1] = { 3,37,954,78 };
	m_miscrt[2] = { 3,37,954,78 };
	m_miscrt[3] = { 3,37,954,78 };
	m_miscrt[4] = { 3,37,954,78 };
	m_miscrt[5] = { 3,37,954,78 };
	m_miscrt[6] = { 3,245,249,78 };
	m_miscrt[7] = { 3,160,249,78 };
	m_miscrt[8] = { 0,330,960,42 };
	m_miscrt[9] = { 0,374,960,42 };
	m_miscrt[10] = { 0,418,960,42 };
	m_miscrt[11] = { 0,0,0,0 };

	m_bkmisc[1].Set(741, 102, 390, 119, 0, 0);
	m_bkmisc[2].Set(741, 150, 390, 119, 0, 0);
}
void LobbyScene::AKeyReact(const INT& index)
{
	switch (index)
	{
	case 1:
		m_bkmisc[1].Set(755, 24, 491, 121, 107, 40);
		m_state = LOBBYSTATE::SELECT;
		break;
	case 2:
		m_bkmisc[1].Set(755, 108, 491, 121, 107, 40);
		m_state = LOBBYSTATE::SELECT;
		break;
	case 3:
		m_bkmisc[1].Set(755, 192, 491, 121, 107, 40);
		m_state = LOBBYSTATE::SELECT;
		break;
	case 4:
		m_bkmisc[1].Set(755, 276, 491, 121, 107, 40);
		m_state = LOBBYSTATE::SELECT;
		break;
	case 5:
		m_bkmisc[1].Set(755, 360, 491, 121, 107, 40);
		m_state = LOBBYSTATE::SELECT;
		break;
	case 6:
		m_state = LOBBYSTATE::SETTING;
		m_miscIndex = 8;
		isSoundBar = true;
		break;
	case 7:
		DestroyWindow(g_hWnd);
		break;
	case 10:
		m_state = LOBBYSTATE::MAINMENU;
		isSoundBar = false;
		m_miscIndex = 6;
		break;
	}
}