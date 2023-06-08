#include "pch.h"
#include "End.h"




End::~End()
{
}

void End::Init()
{
	ending_img.Load(L"리소스\\엔딩.png");
}

void End::Update()
{
}

void End::Render(HDC mdc)
{

	ending_img.Draw(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, ending_img.GetWidth(), ending_img.GetHeight());
}

void End::BoundingBox(HDC mdc)
{
}
