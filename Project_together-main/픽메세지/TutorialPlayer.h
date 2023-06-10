#pragma once
#include "Object.h"
#include "Player.h"


class TutorialPlayer : public Player
{
public:


	TutorialPlayer();
	virtual ~TutorialPlayer() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;

	void jump1();
	void jump2();

	void KnocBackP1();
	void KnocBackP2();


	int& GetCnt3() { return _cnt3; }
public:
	// Player1
	////////////////////////////////////////////////////////////////////

	Pos				_posP1{};			// player1의 실제 위치
	float			_motion_cntP1{ };

	CImage			player1_img_left;
	CImage			player1_img_right;

	CImage          fire_img;

	Motion			_motionP1;

	// 점프
	CImage			player1_img_jump;
	Motion			JumpMotionP1;
	float			JumpTime1 = 0.f;
	float			JumpHeight1 = 0;
	float			jumpPower1 = 45.f;
	float			temp1 = 0;
	BOOL			g_bJumpkeyPressed1 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경

	HDC				mdcP1;
	HBITMAP			hBitmapP1;
	// Player2
	////////////////////////////////////////////////////////////////////
	Pos				_posP2{};			// player2의 실제 위치
	float			_motion_cntP2{ };

	CImage			player2_img_left;
	CImage			player2_img_right;

	Motion			_motionP2;

	// 점프
	CImage			player2_img_jump;
	Motion			JumpMotionP2;
	float			JumpTime2 = 0.f;
	float			JumpHeight2 = 0;
	float			jumpPower2 = 45.f;
	float			temp2 = 0;
	BOOL			g_bJumpkeyPressed2 = FALSE;	//	점프 키 Space bar가 눌리면 TRUE로 변경

	HDC				mdcP2;
	HBITMAP			hBitmapP2;



	int		_cnt3{ 2 };

};

