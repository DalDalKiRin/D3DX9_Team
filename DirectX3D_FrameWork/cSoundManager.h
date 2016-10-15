#pragma once

#include "cSingletonbase.h"
#include <map>

// # fmod.hpp 추가 #
#include "inc/fmod.hpp"

// # lib 링크를 걸어줌 #
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

// # 채널 버퍼 세팅 #
#define SOUNDBUFFER 100
#define EXTRACHANNELBUFFER 50

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class cSoundManager : public cSingletonBase<cSoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System*		pSystem;
	Sound**		ppSound;
	Channel**	ppChannel;

	arrSounds			mTotalSounds;
	map<string, bool>	mSoundUpdate;

public:
	float fMusicVolume;
	float fSoundVolume;

public:
	HRESULT Init(void);
	void	Release(void);
	void	Update(void);

	void AddSound(string KeyName, string SoundName, bool Bgm, bool Loop);
	void Play(string KeyName, float volume = 0.3f);
	void Stop(string KeyName);
	void Pause(string KeyName);
	void Resume(string KeyName);

	bool IsPlaySound(string KeyName);
	bool IsPauseSound(string KeyName);
	
	void SetVolumeValue();
	void SysUpdate();

	cSoundManager();
	~cSoundManager();
};

#define SOUND_MGR cSoundManager::GetInstance()