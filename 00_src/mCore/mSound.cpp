#include "mSound.h"

bool mSound::Init()
{
	m_iEffectList = 0;
	m_iBGMList = 0;
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(g_iMaxSound, FMOD_INIT_NORMAL, 0);
	return true;
}
bool mSound::Frame()
{
	m_pSystem->update();
	return true;
}
bool mSound::Render()
{
	return true;
}
bool mSound::Release()
{
	for (int iSoundNumber = 0; iSoundNumber < g_iMaxSound; ++iSoundNumber)
	{
		m_pEffectSound[iSoundNumber]->release();
		m_pBGMSound[iSoundNumber]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}

INT mSound::LoadEffect(const CHAR* pLoadName, const bool& bPlay)
{
	FMOD::Channel * pChannel = nullptr;
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT, 0, &m_pEffectSound[m_iEffectList]);
	if (bPlay)
	{
		m_pSystem->playSound(m_pEffectSound[m_iEffectList], 0, false, &pChannel);
		m_pEffectCh[m_iEffectList++] = pChannel;
	}
	return m_iEffectList - 1;
}
void mSound::PlayEffect(const INT& iIndex)
{
	FMOD::Channel * pChannel = nullptr;
	m_pSystem->playSound(m_pEffectSound[iIndex], 0, false, &pChannel);
	m_pEffectCh[iIndex] = pChannel;
}
void mSound::VolumeEffect(const INT& iIndex, const FLOAT& fVolume, const bool& bUp)
{
	for (int iEffect = 0; iEffect < m_iEffectList; ++iEffect)
	{
		float fCurrentVolume;
		m_pEffectCh[iIndex]->getVolume(&fCurrentVolume);
		if (bUp)
		{
			fCurrentVolume += fVolume;
			fCurrentVolume = min(1.0f, fCurrentVolume);
		}
		else
		{
			fCurrentVolume -= fVolume;
			fCurrentVolume = max(0.0f, fCurrentVolume);
		}
		m_pEffectCh[iIndex]->setVolume(fCurrentVolume);
	}
}

INT mSound::LoadBGM(const CHAR* pLoadName, const bool& bPlay)
{
	FMOD::Channel * pChannel = nullptr;
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT, 0, &m_pBGMSound[m_iBGMList]);
	if (bPlay)
	{
		m_pSystem->playSound(m_pBGMSound[m_iBGMList], 0, false, &pChannel);
		m_pBGMCh[m_iBGMList++] = pChannel;
	}
	return m_iBGMList - 1;
}
void mSound::PlayBGM(const INT& iIndex, const bool& bPlay, const bool& bLoop)
{
	bool playing = false;
	FMOD::Channel * pChannel = nullptr;
	if (m_pBGMCh[iIndex])
	{
		m_pBGMCh[iIndex]->isPlaying(&playing);
	}
	if (!playing)
	{
		if (bLoop)
		{
			m_pBGMSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			m_pBGMSound[iIndex]->setMode(FMOD_LOOP_OFF);
		}
		m_pSystem->playSound(m_pBGMSound[iIndex], 0, false, &pChannel);
		m_pBGMCh[iIndex] = pChannel;
	}
}
void mSound::VolumeBGM(const INT& iIndex, const FLOAT& fVolume, const bool& bUp)
{
	for (int iBGM = 0; iBGM < m_iBGMList; ++iBGM)
	{
		float fCurrentVolume;
		m_pBGMCh[iIndex]->getVolume(&fCurrentVolume);
		if (bUp)
		{
			fCurrentVolume += fVolume;
			fCurrentVolume = min(1.0f, fCurrentVolume);
		}
		else
		{
			fCurrentVolume -= fVolume;
			fCurrentVolume = max(0.0f, fCurrentVolume);
		}
		m_pBGMCh[iIndex]->setVolume(fCurrentVolume);
	}
}

void mSound::StopBGM(const INT& iIndex)
{
	m_pBGMCh[iIndex]->stop();
}
void mSound::PauseBGM(const INT& iIndex)
{
	bool paused;
	m_pBGMCh[iIndex]->getPaused(&paused);
	m_pBGMCh[iIndex]->setPaused(!paused);
}
void mSound::StopEffect(const INT& iIndex)
{
	m_pEffectCh[iIndex]->stop();
}
void mSound::PauseEffect(const INT& iIndex)
{
	bool paused;
	m_pEffectCh[iIndex]->getPaused(&paused);
	m_pEffectCh[iIndex]->setPaused(!paused);
}