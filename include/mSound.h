#pragma once
#include "Std.h"
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>



const INT g_iMaxSound = 10;

class mSound : public Singleton<mSound>
{
	friend class Singleton<mSound>;
private:
	mSound() {};
public:
	bool				Init		();
	bool				Frame		();
	bool				Render		();
	bool				Release		();
public:
	INT					LoadEffect	(const CHAR*, const bool&);
	void				PlayEffect	(const INT&);
	void				VolumeEffect(const INT&, const FLOAT&, const bool&);
public:
	INT					LoadBGM		(const CHAR*, const bool&);
	void				PlayBGM		(const INT&, const bool& = true, const bool& = true);
	void				VolumeBGM	(const INT&, const FLOAT&, const bool&);
public:
	void				StopBGM		(const INT&);
	void				StopEffect	(const INT&);
	void				PauseBGM	(const INT&);
	void				PauseEffect	(const INT&);
private:
	INT					m_iEffectList;
	INT					m_iBGMList;
	FMOD::System*		m_pSystem;
	FMOD::Channel*		m_pEffectCh[g_iMaxSound];
	FMOD::Channel*		m_pBGMCh[g_iMaxSound];
	FMOD::Sound*		m_pEffectSound[g_iMaxSound];
	FMOD::Sound*		m_pBGMSound[g_iMaxSound];
};


#define S_Sound mSound::getInstance()