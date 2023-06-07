#pragma once
#include "Object.h"


class BackGround :public Object
{
public:


	BackGround();
	virtual ~BackGround() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;
	


	void Render(HDC& mdc, Pos diff1, Pos diff2, ObjectType Choose, bool);



public:

	Pos			_PosP1{};			// player1�� ����
	Pos			_PosP2{};			// player2�� ����
	Pos			_RenderposP1{};		// player1�� ������ ������ ���
	Pos			_RenderposP2{};		// player2�� ������ ������ ���

	HDC			 mdc2;
	HBITMAP		hbit2;
	CImage		background_img;



};

