#include "pch.h"
#include "TutorialPlayer.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "GAME.h"
#include "Object.h"
#include "Misile.h"
TutorialPlayer::TutorialPlayer() :Player()
{
	

}

TutorialPlayer::~TutorialPlayer()
{

	player1_img_left.Destroy();
	player1_img_right.Destroy();
	player1_img_jump.Destroy();
	player1_img_hurt_left.Destroy();
	player1_img_hurt_right.Destroy();


	player2_img_left.Destroy();
	player2_img_right.Destroy();
	player2_img_jump.Destroy();
	player2_img_push.Destroy();
	player2_img_hurt_left.Destroy();
	player2_img_hurt_right.Destroy();
	fire_img.Destroy();
}

void TutorialPlayer::Init() {
	landing1 = true;
	landing2 = true;
	Gravity1 = true;
	Gravity2 = true;
	JumpMotionP1 = Motion::DOWN;
	JumpMotionP2 = Motion::DOWN;
	// Player1
	//==============================================================================//

	player1_img_left.Load(L"리소스\\ch1\\LEFT.png");
	player1_img_right.Load(L"리소스\\ch1\\RIGHT.png");
	player1_img_jump.Load(L"리소스\\ch1\\PINKJUMP.png");
	player1_img_hurt_left.Load(L"리소스\\ch1\\Pink_Monster_Hurt_4_LEFT.png");
	player1_img_hurt_right.Load(L"리소스\\ch1\\Pink_Monster_Hurt_4_RIGHT.png");

	_posP1 = { 50 ,  WINDOW_HEIGHT - 200 };

	
	_motionP1 = Motion::RIGHT;


	//==============================================================================//
	player2_img_left.Load(L"리소스\\ch2\\LEFT.png");
	player2_img_right.Load(L"리소스\\ch2\\RIGHT.png");
	player2_img_jump.Load(L"리소스\\ch2\\Dude_JUMP.png");
	player2_img_push.Load(L"리소스\\ch2\\Dude_Monster_Push.png");
	player2_img_hurt_left.Load(L"리소스\\ch2\\Dude_Monster_Hurt_4_LEFT.png");
	player2_img_hurt_right.Load(L"리소스\\ch2\\Dude_Monster_Hurt_4_RIGHT.png");

	_motionP2 = Motion::LEFT;
	_posP2 = { WINDOW_WIDTH - 100 ,  WINDOW_HEIGHT - 200 };


	size.x = 32;
	size.y = 32;


	_stat.speed = 300;
	fire_img.Load(L"리소스\\fire.png");
}

void TutorialPlayer::Update() {
	float deletaTime = GET_SINGLE(TimeManager)->GetDeltaTime(); //프레임동기화 (컴퓨터마다 속도를 똑같이맞춰줌)

	fire_count += 1;
	fire_count %= 12;

	// player1
	// =========================================================================================

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::A))
	{

		_motionP1 = Motion::LEFT;

		_posP1.x -= _stat.speed * deletaTime;

		_motion_cntP1 += deletaTime * 10;
		if (_motion_cntP1 > 5.f)
			_motion_cntP1 = 0.f;

		if (_posP1.x < 0) {
			_posP1.x = 0;

		}
	}

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::D))
	{
		_motionP1 = Motion::RIGHT;
		_posP1.x += _stat.speed * deletaTime;

		_motion_cntP1 += deletaTime * 10;
		if (_motion_cntP1 > 5.f)
			_motion_cntP1 = 0.f;

		if (_posP1.x + size.x  + 10> WINDOW_WIDTH)
			_posP1.x = WINDOW_WIDTH - size.x - 10;

	}

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::F))
	{
		if (landing1)
		{
			g_bJumpkeyPressed1 = TRUE;
			JumpMotionP1 = Motion::UP;
			landing1 = false;
			fallP1 = true;

		}
	}
	if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::G))
	{

		Missile* missle = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missle->Init();

		missle->SetPos(Pos(_posP1.x, _posP1.y)); //주인공 객체에서 생성


		if (_motionP1 == Motion::RIGHT)
		{
			missle->SetMotion(Bullet_Dir::RIGHT);
		}

		else if (_motionP1 == Motion::LEFT)
		{
			missle->SetMotion(Bullet_Dir::LEFT);
		}

		GET_SINGLE(ObjectManager)->Add(missle);


	}

	// player2
	// ==============================================================================
	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Left))
	{
		_motionP2 = Motion::LEFT;
		_posP2.x -= _stat.speed * deletaTime;

		_motion_cntP2 += deletaTime * 10;
		if (_motion_cntP2 > 5.f)
			_motion_cntP2 = 0.f;


		if (_posP2.x < 0) {
			_posP2.x = 0;
		}
	}

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::Right))
	{
		_motionP2 = Motion::RIGHT;
		_posP2.x += _stat.speed * deletaTime;

		_motion_cntP2 += deletaTime * 10;
		if (_motion_cntP2 > 5.f)
			_motion_cntP2 = 0.f;

		if (_posP2.x + size.x + 10 > WINDOW_WIDTH)
			_posP2.x = WINDOW_WIDTH - size.x - 10;

	}

	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::J))
	{
		if (landing2)
		{
			g_bJumpkeyPressed2 = TRUE;
			JumpMotionP2 = Motion::UP;
			landing2 = false;
			fallP2 = true;

		}
	}
	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::K))
	{
		if (pushBool)
		{
			realpushBool = true;
		}

	}

	else
	{
		pushBool = false;
		realpushBool = false;
	}


	if (Gravity1)
	{
		_posP1.y += 0.5f;
		if (landing1) {
			fallP1 = false;
		}
	}


	if (Gravity2)
	{
		_posP2.y += 0.5f;
		if (landing2)
			fallP2 = false;
	}




	jump1();
	jump2();

	KnocBackP1();
	KnocBackP2();
}

void TutorialPlayer::Render(HDC mdc) {

	// player1
	// ====================================

	hBitmapP1 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP1 = CreateCompatibleDC(mdc);
	SelectObject(mdcP1, (HBITMAP)hBitmapP1);


	int moveCntP1 = static_cast<int>(_motion_cntP1);
	
	if (fallP1) {

		if (JumpMotionP1 == Motion::UP)
		{
			if (_motionP1 == Motion::RIGHT)
				_motion_cntP1 = 0;
			else if (_motionP1 == Motion::LEFT)
				_motion_cntP1 = 2;

			player1_img_jump.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

		if (JumpMotionP1 == Motion::DOWN)
		{
			if (_motionP1 == Motion::RIGHT)
				_motion_cntP1 = 1;
			else if (_motionP1 == Motion::LEFT)
				_motion_cntP1 = 3;

			player1_img_jump.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);

		}
	}
	else if (FIRE)
	{
		fire_img.Draw(mdcP1, 0, 0, size.x, size.y, fire_count * 48, 0, 48, 48);
	}
	else if (_KnocBackP1)
	{
		if (_motionP1 == Motion::LEFT)
		{
			player1_img_hurt_left.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);
		}

		if (_motionP1 == Motion::RIGHT)
		{
			player1_img_hurt_right.Draw(mdcP1, 0, 0, size.x, size.y, _motion_cntP1 * 32, 0, 32, 32);

		}
	}
	else {
		if (_motionP1 == Motion::LEFT)
		{
			player1_img_left.Draw(mdcP1, 0, 0, size.x, size.y, moveCntP1 * 32, 0, 32, 32);
		}

		if (_motionP1 == Motion::RIGHT)
		{

			player1_img_right.Draw(mdcP1, 0, 0, size.x, size.y, moveCntP1 * 32, 0, 32, 32);

		}
	}


	// player2
	// ====================================


	hBitmapP2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	mdcP2 = CreateCompatibleDC(mdc);
	SelectObject(mdcP2, (HBITMAP)hBitmapP2);

	
	int moveCntP2 = static_cast<int>(_motion_cntP2);

	if (fallP2) {
		if (JumpMotionP2 == Motion::UP)
		{
			if (_motionP2 == Motion::RIGHT)
				_motion_cntP2 = 0;
			else if (_motionP2 == Motion::LEFT)
				_motion_cntP2 = 2;

			player2_img_jump.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}

		if (JumpMotionP2 == Motion::DOWN)
		{
			if (_motionP2 == Motion::RIGHT)
				_motion_cntP2 = 1;
			else if (_motionP2 == Motion::LEFT)
				_motion_cntP2 = 3;

			player2_img_jump.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);

		}
	}
	else if (FIRE) {
		fire_img.Draw(mdcP2, 0, 0, size.x, size.y, fire_count * 48, 0, 48, 48);
	}
	else if (_KnocBackP2)
	{
		if (_motionP2 == Motion::LEFT)
		{
			player2_img_hurt_left.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_hurt_right.Draw(mdcP2, 0, 0, size.x, size.y, _motion_cntP2 * 32, 0, 32, 32);

		}
	}
	else if (realpushBool) {
		int moveCnt = static_cast<int>(_motion_cntP2);

		if (_motionP2 == Motion::LEFT)
		{
			player2_img_push.Draw(mdcP2, 0, 0, size.x, size.y, moveCnt * 32, 32, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_push.Draw(mdcP2, 0, 0, size.x, size.y, moveCnt * 32, 0, 32, 32);

		}


	}
	else {
		if (_motionP2 == Motion::LEFT)
		{
			player2_img_left.Draw(mdcP2, 0, 0, size.x, size.y, moveCntP2 * 32, 0, 32, 32);
		}

		if (_motionP2 == Motion::RIGHT)
		{
			player2_img_right.Draw(mdcP2, 0, 0, size.x, size.y, moveCntP2 * 32, 0, 32, 32);

		}
	}


	TransparentBlt(mdc, _posP1.x, _posP1.y, size.x, size.y,
				mdcP1, 0, 0, size.x, size.y, RGB(0, 0, 0));

	TransparentBlt(mdc, _posP2.x, _posP2.y, size.x, size.y,
				mdcP2, 0, 0, size.x, size.y, RGB(0, 0, 0));




	DeleteObject(hBitmapP1);
	DeleteDC(mdcP1);
	DeleteObject(hBitmapP2);
	DeleteDC(mdcP2);

}

void TutorialPlayer::jump1()
{

	if (!g_bJumpkeyPressed1) return;

	Gravity1 = false;
	JumpHeight1 = (JumpTime1 * JumpTime1 - jumpPower1 * JumpTime1) / 4.0f;
	_posP1.y += JumpHeight1 - temp1;
	temp1 = JumpHeight1;

	JumpTime1 += 0.15f;		//값을 올리면 점프속도가 빨라짐

	if (JumpHeight1 < -126.f) {
		JumpMotionP1 = Motion::DOWN;
	}

	if (landing1)
	{
		temp1 = 0;
		JumpTime1 = 0;
		JumpHeight1 = 0;
		Gravity1 = true;
		g_bJumpkeyPressed1 = FALSE;
	}

	if (JumpTime1 > jumpPower1)
	{
		temp1 = 0;
		JumpTime1 = 0;
		JumpHeight1 = 0;
		Gravity1 = true;
		g_bJumpkeyPressed1 = FALSE;
	}

}

void TutorialPlayer::jump2()
{
	if (!g_bJumpkeyPressed2) return;
	Gravity2 = false;
	JumpHeight2 = (JumpTime2 * JumpTime2 - jumpPower2 * JumpTime2) / 4.f;
	_posP2.y += JumpHeight2 - temp2;
	temp2 = JumpHeight2;

	JumpTime2 += 0.15f;		//값을 올리면 점프속도가 빨라짐


	if (JumpHeight2 < -126.f) {
		JumpMotionP2 = Motion::DOWN;
	}


	if (landing2)
	{
		temp2 = 0;
		JumpTime2 = 0;
		JumpHeight2 = 0;
		Gravity2 = true;
		g_bJumpkeyPressed2 = FALSE;
	}

	if (JumpTime2 > jumpPower2)
	{

		temp2 = 0;
		JumpTime2 = 0;
		JumpHeight2 = 0;
		g_bJumpkeyPressed2 = FALSE;
		Gravity2 = true;
	}

}

void TutorialPlayer::KnocBackP1()
{
	if (!_KnocBackP1) return;


	if (_motionP1 == Motion::RIGHT) {

		_motion_cntP1 = 1.f;
		_posP1.x -= 5.f;
		if (_posP1.x < _KnockPosP1.x)
			_KnocBackP1 = false;
	}
	else if (_motionP1 == Motion::LEFT) {
		_motion_cntP1 = 2.f;
		_posP1.x += 5.f;
		if (_posP1.x > _KnockPosP1.x)
			_KnocBackP1 = false;
	}


}

void TutorialPlayer::KnocBackP2()
{
	if (!_KnocBackP2) return;

	if (_motionP2 == Motion::RIGHT) {
		_motion_cntP2 = 1.f;
		_posP2.x -= 5.f;
		if (_posP2.x < _KnockPosP2.x)
			_KnocBackP2 = false;
	}
	else if (_motionP2 == Motion::LEFT) {
		_motion_cntP2 = 2.f;
		_posP2.x += 5.f;
		if (_posP2.x > _KnockPosP2.x)
			_KnocBackP2 = false;
	}
}

void TutorialPlayer::BoundingBox(HDC mdc){
	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	RECT BoxP1{ _posP1.x, _posP1.y, _posP1.x + size.x, _posP1.y + size.y };

	RECT BoxP2{ _posP2.x, _posP2.y, _posP2.x + size.x, _posP2.y + size.y };





	FrameRect(mdc, &BoxP1, hBrush);
	FrameRect(mdc, &BoxP2, hBrush);

	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);
}