
#pragma once
#include "Object.h"

class Tile_Push : public Object
{

public:

	Tile_Push();

	virtual ~Tile_Push() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;


private:
	HDC			mdc2;
	HBITMAP		hBitmap2;

	CImage      tile_img;

	Pos			_Renderpos{};		// ������ ��ǥ

	WCHAR test[100];

	BOOL  _rand1;
};