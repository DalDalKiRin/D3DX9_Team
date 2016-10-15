#include "stdafx.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
	: pSystem(NULL)
	, ppSound(NULL)
	, ppChannel(NULL)
	, fMusicVolume(0.3f)
	, fSoundVolume(0.3f)
{
}


cSoundManager::~cSoundManager()
{
}

HRESULT cSoundManager::Init(void)
{
	// # 사운드 시스템 초기화 #
	System_Create(&pSystem);

	pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	ppSound = new Sound*[TOTALSOUNDBUFFER];
	ppChannel = new Channel*[TOTALSOUNDBUFFER];

	memset(ppSound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(ppChannel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void cSoundManager::Release(void)
{
}

void cSoundManager::Update(void)
{
	SysUpdate();
}

void cSoundManager::AddSound(string KeyName, string SoundName, bool Bgm, bool Loop)
{
	if (Loop)
	{
		if (Bgm)
			pSystem->createStream(SoundName.c_str(), FMOD_LOOP_NORMAL, 0, &ppSound[mTotalSounds.size()]);
		else
			pSystem->createSound(SoundName.c_str(), FMOD_LOOP_NORMAL, 0, &ppSound[mTotalSounds.size()]);
	}
	else
	{
		if (Bgm)
			pSystem->createStream(SoundName.c_str(), FMOD_DEFAULT, 0, &ppSound[mTotalSounds.size()]);
		else
			pSystem->createSound(SoundName.c_str(), FMOD_DEFAULT, 0, &ppSound[mTotalSounds.size()]);
	}

	mTotalSounds.insert(make_pair(KeyName, &ppSound[mTotalSounds.size()]));
	mSoundUpdate.insert(make_pair(KeyName, Bgm));
}

void cSoundManager::Play(string KeyName, float volume)
{
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			pSystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &ppChannel[count]);
			ppChannel[count]->setVolume(volume);
			break;
		}
	}
}

void cSoundManager::Stop(string KeyName)
{
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			ppChannel[count]->stop();
			break;
		}
	}
}

void cSoundManager::Pause(string KeyName)
{
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			ppChannel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::Resume(string KeyName)
{
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			ppChannel[count]->setPaused(false);
			break;
		}
	}
}

bool cSoundManager::IsPlaySound(string KeyName)
{
	bool isPlay = false;
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			ppChannel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool cSoundManager::IsPauseSound(string KeyName)
{
	bool isPause = false;
	arrSoundsIter iter = mTotalSounds.begin();

	int count = 0;

	for (iter; iter != mTotalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			ppChannel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void cSoundManager::SetVolumeValue()
{
	map<string, bool>::iterator iter = mSoundUpdate.begin();

	int count = 0;

	for (iter; iter != mSoundUpdate.end(); ++iter, count++)
	{
		if (iter->second)
			ppChannel[count]->setVolume(fMusicVolume);
		else if (!iter->second)
		{
			ppChannel[count]->setVolume(fSoundVolume);
		}
	}
}

void cSoundManager::SysUpdate()
{
	pSystem->update();
}
