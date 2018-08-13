#pragma once
#include <Std.h>
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>


#pragma comment(lib, "fmod64_vc.lib")

class Sound
{
public:
	static Sound& GetInstance()
	{
		static Sound getinst;
		return getinst;
	}
private:
	Sound();
public:
	virtual ~Sound();
public:
	bool				Init		();
	bool				Frame		();
	bool				Render		();
	bool				Release		();
public:
	int					Load		(const char*, bool);
	void				Play		(const int&, bool = true, bool = false);
	void				PlayEffect	(const int&);
	void				Stop		(const int&);
	void				Pause		(const int&);
	void				Volume		(const int&, const float&, bool);
private:
	TCHAR				m_szBuffer[MAX_PATH];
	int					m_iSoundList;
	static const int	m_iMaxSound = 32;
	FMOD::System*		m_pSystem;
	FMOD::Sound*		m_pSound[m_iMaxSound];
	FMOD::Channel*		m_pChannel[m_iMaxSound];
};