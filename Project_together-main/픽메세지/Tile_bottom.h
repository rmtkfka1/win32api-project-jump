#pragma once
#include "Object.h"

class Tile_bottom : public Object
{

public:

	Tile_bottom();
	virtual ~Tile_bottom() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;


protected:
	HDC			mdc2;
	HBITMAP		hBitmap2;


	CImage      tile_img;
	Pos			_Renderpos{};		// ·»´õ¸µ ÁÂÇ¥




};
