#pragma once
#include "SingletonBase.h"
//#include <fmod.h>
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")

using namespace FMOD;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	System *System = nullptr;
	Sound *Sound = nullptr;
	Channel *Channel = nullptr;


	typedef map<string, FMOD::Sound*> mapSoundList;
	typedef map<string, FMOD::Sound*>::iterator mapSoundIter;

public:
	mapSoundList _mSoundList;
	HRESULT init(void);
	void release(void);
	void update(void);

	FMOD::Sound* addSound(string strKey, string dir, bool isloop);
	FMOD::Sound* findSound(string strKey);
	void playSound(string strKey, float vol);

	//void setVolume(float vol);
	bool deleteSound(string strKey);
	bool deleteAll();

	SoundManager() {}
	~SoundManager() {}

};

