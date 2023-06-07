#pragma once
#include "Object.h"
class Tile_Climb2 : public Object
{

public:

	Tile_Climb2();
	virtual ~Tile_Climb2() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;


private:
	HDC			mdc2;
	HBITMAP		hBitmap2;

	CImage      tile_img;

	Pos			_Renderpos{};		// ������ ��ǥ
	WCHAR test[100];

	BOOL       CHECK;
};
