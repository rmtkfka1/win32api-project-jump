#include "pch.h"
#include "End.h"




End::~End()
{
}

void End::Init()
{
}

void End::Update()
{
}

void End::Render(HDC mdc)
{
	TextOut(mdc, 0, 0, L"�����!", lstrlen(L"�����!"));
}

void End::BoundingBox(HDC mdc)
{
}
