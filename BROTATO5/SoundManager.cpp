#include "Stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&System);
	if (result != FMOD_OK)
	{
		return E_FAIL;
	}
	result = System->init(32, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		return E_FAIL;
	}
	return S_OK;
}

void SoundManager::release(void)
{
	this->deleteAll();

}

void SoundManager::update(void)
{
	System->update();
}

//키값, 사운드 맵에 페어 등록
FMOD::Sound* SoundManager::addSound(string strKey, string dir, bool isloop)
{
	FMOD::Sound* snd = findSound(strKey);
	
	if (snd)
	{
		return snd;
	}
	if (isloop)
	{
		if (FAILED(System->createSound(dir.c_str(), FMOD_LOOP_NORMAL, 0, &snd)))
		{
			SAFE_DELETE(snd);
			return NULL;
		}
	}
	else
	{
		if (FAILED(System->createSound(dir.c_str(), FMOD_LOOP_OFF, 0, &snd)))
		{
			SAFE_DELETE(snd);
			return NULL;
		}
	}
	_mSoundList.insert(pair<string, FMOD::Sound*>(strKey, snd));

	return snd;
}

FMOD::Sound* SoundManager::findSound(string strKey)
{
	auto key = _mSoundList.find(strKey);

	if (key != _mSoundList.end())
	{
		return key->second;
	}
	return nullptr;
}

void SoundManager::playSound(string strKey, float vol)
{
	Channel->setVolume(vol);
	System->playSound(findSound(strKey), 0, false, &Channel);
}

bool SoundManager::deleteSound(string strKey)
{
	auto key = _mSoundList.find(strKey);

	if (key != _mSoundList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mSoundList.erase(key);

		return true;
	}

	return false;
}

bool SoundManager::deleteAll()
{
	auto iter = _mSoundList.begin();
	for (; iter != _mSoundList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSoundList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSoundList.clear();
	return true;

}
