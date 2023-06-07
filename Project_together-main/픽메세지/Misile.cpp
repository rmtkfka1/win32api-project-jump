#include "pch.h"
#include "Misile.h"
#include "pch.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Player.h"
#include <chrono>
#include <thread>
Missile::Missile() :Object(ObjectType::MISSILE)
{
}

Missile::~Missile()
{
	bullet_img.Destroy();
}

void Missile::Init()
{
	size.x = 20;
	size.y = 20;
	_stat.hp = 1;
	_stat.maxhp = 1;
	_stat.speed = 1000;
	bullet_img.Load(L"���ҽ�\\Bullet.png");
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


	//�浹ó������//
	const vector<Missile*>& msilles = GET_SINGLE(ObjectManager)->GetMissile();   //���͸� �������°�
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //���͸� �������°�
	Player* p = player[0];
	
	for (int i = 0; i < msilles.size(); ++i)
	{
		RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y +p->GetSize().y};
		RECT missile_rect = { msilles[i]->GetPos().x,msilles[i]->GetPos().y,msilles[i]->GetPos().x + msilles[i]->GetSize().x
			,msilles[i]->GetPos().y + msilles[i]->GetSize().y};
		RECT intersect_rect;

		if (IntersectRect(&intersect_rect, &missile_rect, &p2_rect))
		{
			
			p->CollisionGap();

			Pos temp = p->_posP2;
			p->_posP2 = p->_posP1;
			p->_posP1 = temp;
			p->FIRE = true;

			GET_SINGLE(ObjectManager)->Remove(msilles[i]);   //���͸� �������°�

		
			std::thread resetFireThread([p]() {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				p->FIRE = false;
				});

			resetFireThread.detach();
			return;
		}
	}

	if (_pos.x > 6000)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return; //�����ϸ� ������ ������ �������Ѵ�.
	}

	if (_pos.x < -6000)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return; //�����ϸ� ������ ������ �������Ѵ�.
	}


};



void Missile::Render(HDC mdc)
{


	mdc2 = CreateCompatibleDC(mdc);
	hBitmap2 = CreateCompatibleBitmap(mdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(mdc2, (HBITMAP)hBitmap2);


	bullet_img.Draw(mdc2, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight()
		, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight());

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //���͸� ��������

	Player* p = player[0];


	Pos diff = p->GetDiffP1();
	Pos diff2 = p->GetDiffP2();

	if (p->_turn == ObjectType::PLAYER1)            // ������ 1�� ��
		_Renderpos = _pos - diff;                // << player1�� ��
	else if (p->_turn == ObjectType::PLAYER2)        // ������ 2
		_Renderpos = _pos - diff2;                // << player2�� ��


	TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x, size.y,
		mdc2, 0, 0, bullet_img.GetWidth(), bullet_img.GetHeight(), RGB(0, 0, 0));


	DeleteObject(hBitmap2);
	DeleteDC(mdc2);
	// ȭ�� ���� �Ѿ� �κ� �ذ� ����


}

