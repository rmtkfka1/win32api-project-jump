#pragma once
#include "Object.h"

class Tile_Switch : public Object
{

public:

	Tile_Switch();
	virtual ~Tile_Switch() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;


private:
	HDC			mdc2;
	HBITMAP		hBitmap2;


	CImage      tile_img;
	Pos			_Renderpos{};		// ������ ��ǥ

public:
	BOOL        TURNON;


};