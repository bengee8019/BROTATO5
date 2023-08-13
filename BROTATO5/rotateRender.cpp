#include "Stdafx.h"
#include "rotateRender.h"

rotateRender::rotateRender()
{
}

rotateRender::~rotateRender()
{
}

void rotateRender::init()
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	gdiplusToken = 0;
}

void rotateRender::addImage(wchar_t* fileName)
{
	image = Image::FromFile(fileName);
}

//void rotateRender::Render(HDC hdc, int x, int y, float angle)
//{
//    Graphics graphics(hdc);
//    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
//
//    // 회전 중심을 이미지 중심으로
//    int centerX = x + image->GetWidth() / 2;
//    int centerY = y + image->GetHeight() / 2;
//    int hWidth = image->GetWidth() / 2;
//    int hHeight = image->GetHeight() / 2;
//    graphics.TranslateTransform(centerX, centerY);
//    graphics.RotateTransform(angle);
//    graphics.TranslateTransform(-centerX, -centerY);
//
//    graphics.DrawImage(image, x-hWidth, y-hHeight);
//}

void rotateRender::Render(HDC hdc, int x, int y, float angle)
{
    Gdiplus::Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    // 회전 중심을 이미지 중심으로
    int centerX =image->GetWidth() / 2;
    int centerY =image->GetHeight() / 2;
    graphics.TranslateTransform(x, y);
    graphics.RotateTransform(angle);
    graphics.TranslateTransform(-x, -y);

    graphics.DrawImage(image, x - centerX, y - centerY);
}

void rotateRender::release()
{
    SAFE_DELETE(image);

    if (gdiplusToken)
    {
        GdiplusShutdown(gdiplusToken);
    }
}
