#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init(void)
{
	//
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();

	//mciSendString(): 장치에 특정 명령어를 전송하여 구동시키는 함수
	//(문자열 명령어, 반환값을 알려줄 명령어, 반환될 길이, 핸들 콜백)
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();

	//mciSendString(): 장치에 특정 명령어를 전송하여 구동시키는 함수
	//(문자열 명령어, 반환값을 알려줄 명령어, 반환될 길이, 핸들 콜백)
	// 핸들콜백 -> 같이 실행할게 있으면 
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	//PlaySound(): TEXT("파일 이름.wav"), 파일명을 사용하면 NULL, 아니면 해당 인스턴스 핸들
	//fdwSound (옵션|옵션2|옵션3 등등)
	//SND_ASYNC : 재생하면서 다음 코드를 실행 ( 비동기 플래그 )
	/*
	SND_LOOP: 반복 재생
	SND_NODEFAULT: 지정한 경로에 파일이 없어도 경고음 재생x
	*/
	PlaySound(fileName, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);

}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";		
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}



TempSoundManager::TempSoundManager()
{
}

TempSoundManager::~TempSoundManager()
{
}
