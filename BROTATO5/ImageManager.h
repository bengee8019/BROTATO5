#pragma once
#include "SingletonBase.h"
#include "GImage.h"

// 1. 객체에 따른 new	
// 2. 관리 문제				2번 우선적으로 생각
// ㄴ STL -> Map


#pragma region STL MAP
/*
KEY 와 VALUE

first -> key
second -> value

insert()를 통해  key 와 value를 쌍으로 가진 pair를 받는다.

-pair() 두가지 자료형을 하나로 묶어주는 구조체 ( 템플릿으로 어떤 자료형이라도 가능하다.)

-make_pair(): pair를 만들어주는 함수
ㄴ pair.first = x, pair.second = y
ㄴ pair = make_pair(x, y)

하나의 키에 여러 값을 저장하고 싶다면 멀티맵을 사용해볼 수 있다.

pair를 확장시켜 구조를 작성하거나 다수의 반환값을 가지고 싶다면 tuple을 고려해보자.


*/
#pragma endregion

//객체의 고유성을 보존하기 위한 singleton
class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;

private:
	mapImageList _mImageList;
	//만약 string대신 char*를 쓴다면?? 스마트포인터 iterator에서 
		//1. 호환성 문제, 2. 반복시마다 참조하면서 속도 느려짐


public:
	HRESULT init(void);
	void release(void);

	//단독 처리시 문제점
	// ㄴ 1. 프레임워크 코드 불일치
	// ㄴ 2. 객체간 (이미지) 충돌 가능성


	GImage* addImage(string strKey, int width, int height);
	// 이미지 파일로 초기화
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));



	//1번쓰는 배경 등
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	//
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	//플레이어 객체 등에 활용
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));


	GImage* findImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();


	// 렌더
	void render(string str, HDC hdc);
	void render(string str, HDC hdc, int destX, int destY);
	void render(string str, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	// 이미지 클리핑
	void render(string str, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	// 알파렌더
	void alphaRender(string str, HDC hdc, BYTE alpha);
	void alphaRender(string str, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string str, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(string str, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 렌더
	void frameRender(string str, HDC hdc, int destX, int destY);
	void frameRender(string str, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//루프랜더
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//LPIMAGE_INFO getImageInfo() { return _imageInfo; }



	ImageManager();
	~ImageManager();
};

