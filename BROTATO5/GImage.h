#pragma once
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, LOAD_FILE,		// 리소스, 파일
		LOAD_EMPTY, LOAD_END				// 빈 비트맵, 로드 Done
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;						//이미지 x좌표
		float		y;						//이미지 y좌표
		int			width;					//이미지 가로 크기
		int			height;					//이미지 세로 크기
		int			currentFrameX;			//현재 프레임 x
		int			currentFrameY;			//현재 프레임 y
		int			maxFrameX;				//최대 프레임 x 갯수
		int			maxFrameY;				//최대 프레임 y 갯수
		int			frameWidth;				//
		int			frameHeight;			//
		BYTE		loadType;				

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	char*			_fileName;
	bool			_isTrans;			// 없앨건지?
	COLORREF		_transColor;		// 없앨 RGB 값 (마젠타 = RGB(255, 0, 255)

	/*
	COLORREF

	- 윈도우즈 색상값을 표현하기 위한 부호없는 32비트 정수형
	ㄴ R, G, B 각각 1바이트(8비트)이며 0~255까지의 값을 표현하는데 최적화 되어 있다.
	*/

	BLENDFUNCTION	_blendFunc;			// 알파블렌드 기능
	LPIMAGE_INFO	_blendImage;		// 알파블렌드 이미지

public:
	HRESULT init(int width, int height);

	// 이미지 리소스로 초기화
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));



	//1번쓰는 배경 등
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));

	//
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));

	//플레이어 객체 등에 활용
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));


	HRESULT initForAlphaBlend(void);

	// 투명 Color키 세팅
	void setTransColor(bool isTrans, COLORREF transColor);

	// 해제
	void release(void);

	// 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	// 이미지 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	// 알파렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	LPIMAGE_INFO getImageInfo() { return _imageInfo; }

	// = 인라인 함수 =
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	
	//이미지 X좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 Y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로 / 세로 크기
	inline int getwidth(void) { return _imageInfo->width; }
	inline int getheight(void) { return _imageInfo->height; }

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->width,
			_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->frameWidth,
			_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{ 
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 1프레임 가로 / 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대 프레임 X / Y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	//==================루프랜더====================
  // ㄴ 반복 / 이미지를 밀고 당기는 방식 
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY); //ex) 슈팅게임 배경, 러닝게임 배경 (활용하면 카메라구현가능)
							//그려지는 영역
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	GImage();
	~GImage() {}
};

