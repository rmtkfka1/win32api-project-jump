#include "pch.h"
#include "Misile.h"
#include "pch.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Player.h"
#include <chrono>
#include <thread>
#include "TutorialPlayer.h"

Missile::Missile() :Object(ObjectType::MISSILE)
{
}

Missile::~Missile()
{
	bullet_img.Destroy();



	
}

void Missile::Init()
{
	size.x = 30;
	size.y = 20;
	_stat.hp = 1;
	_stat.maxhp = 1;
	_stat.speed = 1000;
	bullet_img.Load(L"리소스\\Bullet.png");


}

void Missile::Update()
{

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_motion == Bullet_Dir::RIGHT)
	{
		_pos.x += _stat.speed * deltaTime;
	}
	if (_motion == Bullet_Dir::LEFT)
	{
		_pos.x -= _stat.speed * deltaTime;
	}


	//충돌처리구현//

	RECT missile_rect = { _pos.x, _pos.y, _pos.x + size.x, _pos.y + size.y };
	RECT intersect_rect;

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는것

	if (player.size() != 0) {
		Player* p = player[0];
		RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
		if (IntersectRect(&intersect_rect, &missile_rect, &p2_rect))
		{
			p->_swap = true;
			p->CollisionGap();
			Pos temp = p->_posP2;
			p->_posP2 = p->_posP1;
			p->_posP1 = temp;
			p->FIRE = true;
			GET_SINGLE(ObjectManager)->Remove(this);   //벡터를 가져오는것
			std::thread resetFireThread([p]() {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			p->FIRE = false;
				});
			resetFireThread.detach();
			return;
		}

		if (_pos.x > 6000)
		{
			GET_SINGLE(ObjectManager)->Remove(this);
			return; //삭제하면 무조건 리턴을 떄려야한다.
		}

		if (_pos.x < -6000)
		{
			GET_SINGLE(ObjectManager)->Remove(this);
			return; //삭제하면 무조건 리턴을 떄려야한다.
		}
	}
	
	const vector<TutorialPlayer*>& tplayer = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	if (tplayer.size() != 0) {
		TutorialPlayer* tp = tplayer[0];
		RECT p2_rect = { tp->_posP2.x, tp->_posP2.y,tp->_posP2.x + tp->GetSize().x ,tp->_posP2.y + tp->GetSize().y };
		
		if (IntersectRect(&intersect_rect, &missile_rect, &p2_rect))
		{
			tp->_swap = true;
			Pos temp = tp->_posP2;
			tp->_posP2 = tp->_posP1;
			tp->_posP1 = temp;
			tp->FIRE = true;
			GET_SINGLE(ObjectManager)->Remove(this);   //벡터를 가져오는것
			std::thread resetFireThread([tp]() {
				std::this_thread::sleep_for(std::chrono::seconds(1s));
			tp->FIRE = false;
				});
			resetFireThread.detach();

			--tp->GetCnt3();
			return;
		}
		if (_pos.x > WINDOW_WIDTH)
		{
			GET_SINGLE(ObjectManager)->Remove(this);
			return; //삭제하면 무조건 리턴을 떄려야한다.
		}

		if (_pos.x < 0)
		{
			GET_SINGLE(ObjectManager)->Remove(this);
			return; //삭제하면 무조건 리턴을 떄려야한다.
		}
		
	}

	

};



void Missile::Render(HDC mdc)
{


	mdc2 = CreateCompatibleDC(mdc);
	hBitmap2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(mdc2, (HBITMAP)hBitmap2);


	bullet_img.Draw(mdc2, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight()
		, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight());

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
	if (player.size() != 0) {
		Player* p = player[0];


		Pos diff = p->GetDiffP1();
		Pos diff2 = p->GetDiffP2();

		if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
			_Renderpos = _pos - diff;                // << player1일 때
		else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
			_Renderpos = _pos - diff2;                // << player2일 때


		TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x, size.y,
			mdc2, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight(), RGB(0, 0, 0));
	}
	const vector<TutorialPlayer*>& tplayer = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	if (tplayer.size() != 0) {


		TransparentBlt(mdc, _pos.x, _pos.y, size.x, size.y,
			mdc2, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight(), RGB(0, 0, 0));
	}

	DeleteObject(hBitmap2);
	DeleteDC(mdc2);

}

void Missile::BoundingBox(HDC mdc) {
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

	Player* p = player[0];

	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	RECT Box{ _pos.x, _pos.y, _pos.x + size.x, _pos.y + size.y };
	RECT RenderBox{ _Renderpos.x, _Renderpos.y, _Renderpos.x + size.x, _Renderpos.y + size.y };


	if (p->_turn == ObjectType::PLAYER1) {
		RenderBox.left = Box.left - p->_DiffP1.x;
		RenderBox.top = Box.top - p->_DiffP1.y;
		RenderBox.right = Box.right - p->_DiffP1.x;
		RenderBox.bottom = Box.bottom - p->_DiffP1.y;
	}
	else if (p->_turn == ObjectType::PLAYER2) {
		RenderBox.left = Box.left - p->_DiffP2.x;
		RenderBox.top = Box.top - p->_DiffP2.y;
		RenderBox.right = Box.right - p->_DiffP2.x;
		RenderBox.bottom = Box.bottom - p->_DiffP2.y;
	}




	FrameRect(mdc, &RenderBox, hBrush);


	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);
}