#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{	
		//GetTickCount() : API 공용함수
		//ㄴ API 함수로 OS가 부팅된 후의 경과 기간을 체크해 준다.
		//ㄴ 밀리세컨 단위로 체크가 가능하며 밀리세컨 단위로 시간값을 반환하기 때문에
		//   규모가 크지 않는 로직에 적합하다.
		srand(GetTickCount()); //윈도우에 맡기겠다 찍어라
	}
	~RandomFunction() {}

	inline int getInt(int num)
	{
		return rand() % num;
	}
	HRESULT init(void){ return S_OK; }
	// 0 을 조심하자
	inline int getFromInTo(int fromNum, int toNum)
	{
		// if 
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / RAND_MAX * num;
	}
	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
	//void getShape(int x1, int y1,int x2, int y2)
	//{
	//	LineTo(hdc, x1, y1);
	//	MoveToEx(hdc, x2,y2,NULL);
	//	//선
	//	LineTo(hdc, x1, y1);
	//	MoveToEx(hdc, x2, y2, NULL);
	//	LineTo(hdc, x2, y2);
	//	MoveToEx(hdc, x1 + 50, y2, NULL);
	//	//삼각형

	//	Rectangle(hdc,x1, y1, x2, y2);
	//	//사각형
	//	Ellipse(hdc, x1, y1, x2, y2);
	//	//원
	//}
	
};