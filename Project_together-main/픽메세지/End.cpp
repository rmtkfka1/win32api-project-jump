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
	TextOut(mdc, 0, 0, L"¼ö°í¿ç!", lstrlen(L"¼ö°í¿ç!"));
}

void End::BoundingBox(HDC mdc)
{
}
