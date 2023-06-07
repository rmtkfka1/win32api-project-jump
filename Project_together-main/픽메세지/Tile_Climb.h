#pragma once
#include "Object.h"
class Tile_Climb : public Object
{

public:

	Tile_Climb();
	virtual ~Tile_Climb() override;
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

