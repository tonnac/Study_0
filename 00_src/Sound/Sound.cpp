#include "Sound.h"

bool Sound::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	return true;
}
bool Sound::Frame()
{
	m_pSystem->update();

	unsigned int total = 0;
	unsigned int ms = 0;
	m_pSound[0]->getLength(&total,FMOD_TIMEUNIT_MS);
	m_pChannel[0]->getPosition(&ms,FMOD_TIMEUNIT_MS);

	_stprintf_s(m_szBuffer, L"[%02d:%02d:%02d]<-->"
							"[%02d:%02d:%02d]",
		total / 1000 / 60,
		total / 1000 % 60,
		total / 10 % 60,
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 60);

	return true;
}
bool Sound::Render()
{
	SetTextColor(g_hOffScreenDC, RGB(102, 255, 255));
	SetBkColor(g_hOffScreenDC, RGB(0, 0, 0));
//	SetBkMode(g_hOffScreenDC, TRANSPARENT);
	TextOut(g_hOffScreenDC, 0, 34, m_szBuffer, static_cast<int>(_tcsclen(m_szBuffer)));
	return true;
}
bool Sound::Release()
{
	for (int iSound = 0; iSound < m_iMaxSound; ++iSound)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
int Sound::Load(const char* pLoadName, bool bPlay)
{
	FMOD::Channel * pChannel = nullptr;
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT,
		0, &m_pSound[m_iSoundList]);
	if (bPlay == true)
	{
		m_pSystem->playSound(m_pSound[m_iSoundList], 0, false, &pChannel);
		m_pChannel[m_iSoundList++] = pChannel;
	}
	return m_iSoundList - 1;
}
void Sound::Play(const int& iIndex, bool bPlay, bool bLoop)
{
	bool playing = false;
	FMOD::Channel * pChannel = nullptr;
	if (m_pChannel[iIndex])
	{
		m_pChannel[iIndex]->isPlaying(&playing);
	}
	if (playing == false)
	{
		if (bLoop)
		{
			m_pSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			m_pSound[iIndex]->setMode(FMOD_LOOP_OFF);
		}
		m_pSystem->playSound(m_pSound[iIndex], 0, false, &pChannel);
		m_pChannel[iIndex] = pChannel;
	}
}
void Sound::PlayEffect(const int&iIndex)
{
	FMOD::Channel * pChannel = nullptr;
	m_pSystem->playSound(m_pSound[iIndex], 0, false, &pChannel);
	m_pChannel[iIndex] = pChannel;
}
void Sound::Stop(const int& iIndex)
{
	m_pChannel[iIndex]->stop();
}
void Sound::Pause(const int& iIndex)
{
	bool paused;
	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}
void Sound::Volume(const int& iIndex, const float& fVolume, bool bUp)
{
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
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
	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}
Sound::Sound() : m_iSoundList(0)
{
}

Sound::~Sound()
{
}