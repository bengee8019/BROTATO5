#pragma once
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

class rotateRender
{
private:
    Image* image;
    ULONG_PTR gdiplusToken;

public:
    rotateRender();

    ~rotateRender();

    void init();

	void addImage(wchar_t* fileName);

    void Render(HDC hdc, int x, int y, float angle);

    void release();
};

