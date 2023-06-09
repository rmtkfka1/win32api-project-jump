#pragma once
#include "Object.h"


class Monster : public Object
{
public:

	Monster();
	virtual ~Monster() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;

private:
	HDC			mdc2;
	HBITMAP		hBitmap2;

	CImage      tile_img;
	Pos			_Renderpos{};		// ·»´õ¸µ ÁÂÇ¥

public:

	Pos			_move_range;
	//Pos        _first_move_renge;
	BOOL        _DoyouWant_UP;
	BOOL        _isMovingUp;
	BOOL        _isMovingLeft;
	int         counting;

};

