#pragma once
#include "TStd.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod64_vc.lib")
using namespace FMOD;
const int g_iMaxSound = 32;
class TSound
{
public:
	static TSound* Get()
	{
		static TSound sound;
		return &sound;
	}
public:
	FMOD::System*   m_pSystem;
	FMOD::Sound*	m_pSound[g_iMaxSound];
	FMOD::Channel*  m_pChannel[g_iMaxSound];
	int   m_iSoundList;
	TCHAR     m_szBuffer[MAX_PATH];
public:
	bool	Init();
	bool	Frame();
	bool	Release();
	bool	Render();
public:
	int     Load(const char* pLoadName, bool bPlay);
	void    Play(int iIndex, bool bPlay=true, bool bLoop=false);
	void    PlayEffect(int iIndex);
	void    Stop(int iIndex);
	void    paused(int iIndex);
	void    Volume(int iIndex, float fVolume, bool bUp);
private:
	TSound();
public:
	virtual ~TSound();
};

