#pragma once
#include "SingletonBase.h"
// 윈도우 내장된 라이브러리(재생)
// 시간 또는 사운드 관련 -> PlaySound()
#include <mmsystem.h>
// 장치관리자에 관한 api tool
// mciSendString() 함수를 사용하기 위해 추가
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:
	HRESULT init(void);
	//Mp3
	void addMp3FileWithKey(string key, string fileName);
	//Wav
	void addWaveFileWithKey(string key, string fileName);
	//효과음
	void playEffectSoundWave(char* fileName);
	//Mp3 재생
	void playSoundWithKey(string key);
	//정지
	void stopMp3WithKey(string key);

	TempSoundManager();
	~TempSoundManager();
};

