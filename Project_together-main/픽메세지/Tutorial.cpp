#include "pch.h"
#include "Tutorial.h"
#include "KeyManager.h"
#include "SceanManager.h"
#include "TutorialPlayer.h"
#include "ObjectManager.h"
#include "TutorialBottom.h"
#include "Tile_bottom.h"
#include "Tile_Push.h"
#include "Tile_KnockBack.h"
#include "Misile.h"

Tutorial::~Tutorial()
{
	GET_SINGLE(ObjectManager)->Clear();
	ssystem->release();

}

void Tutorial::Init()
{
	TutorialPlayer* player = GET_SINGLE(ObjectManager)->CreateObject<TutorialPlayer>();
	player->Init();
	GET_SINGLE(ObjectManager)->Add(player);
	
	TutorialBottom* tile = GET_SINGLE(ObjectManager)->CreateObject<TutorialBottom>();
	tile->Init();
	GET_SINGLE(ObjectManager)->Add(tile);

	MakeTile_PUSH(300, 420);
	
	Tile_KnockBack* tile_knockback = GET_SINGLE(ObjectManager)->CreateObject<Tile_KnockBack>();
	tile_knockback->Init();

	tile_knockback->SetSize(Pos(50, 50));
	tile_knockback->SetPos(Pos(800, 400 + 20));
	GET_SINGLE(ObjectManager)->Add(tile_knockback);


	result = FMOD::System_Create(&ssystem);

	ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ssystem->createSound("Sound\\Tutorial.wav",
		FMOD_LOOP_NORMAL, 0, &sound1);
	ssystem->playSound(sound1, 0, false, &channel);
	
}



void Tutorial::Update()
{
	// 항상
	// ========================================================================================
	const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	player[0]->Update();

	const vector<TutorialBottom*>& tile_bottom = GET_SINGLE(ObjectManager)->GetTutorailBottom();
	for (int i = 0; i < tile_bottom.size(); ++i)
	{
		tile_bottom[i]->Update();
		
	}
	// ========================================================================================


	// 설명1
	if (sequence == 0)
		BallCollision();


	// 설명2
	if (sequence == 1) {
		BallCollision();

		const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
		for (int i = 0; i < tile_push.size(); ++i)
		{
			tile_push[i]->Update();
		}

		const vector<Tile_KnockBack*> tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();
		for (int i = 0; i < tiles_knockback.size(); ++i)
		{
			tiles_knockback[i]->Update();
		}

	}
	if (sequence == 2) {
		const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();
		for (int i = 0; i < missiles.size(); ++i)
		{
			missiles[i]->Update();
		}
	}

	




}

void Tutorial::Render(HDC mdc)
{	
	// 항상
	// ========================================================================================
	const vector<TutorialBottom*>& tile_bottom = GET_SINGLE(ObjectManager)->GetTutorailBottom();
	for (int i = 0; i < tile_bottom.size(); ++i)
	{
		tile_bottom[i]->Render(mdc);
		//tile_bottom[i]->BoundingBox(mdc);
	}
	const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	player[0]->Render(mdc);
	player[0]->BoundingBox(mdc);

	// 설명1
	if (sequence == 0) {
		ExPlain1(mdc);
		if (!_start[_cnt] && !_end[_cnt]) {
			_start[0] = true;
		}
		else if (_start[_cnt] && !_end[_cnt]) {
			this_thread::sleep_for(1000ms);
			_end[_cnt] = true;
		}
	}

	// 설명2

	if (sequence == 1) {
		ExPlain2(mdc);

		if (!_start[_cnt] && !_end[_cnt]) {
			_start[_cnt] = true;
		}
		else if (_start[_cnt] && !_end[_cnt]) {
			this_thread::sleep_for(1000ms);
			_end[_cnt] = true;
		}

		const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
		for (int i = 0; i < tile_push.size(); ++i)
		{
			tile_push[i]->Render(mdc);
		}

		const vector<Tile_KnockBack*> tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();
		for (int i = 0; i < tiles_knockback.size(); ++i)
		{
			tiles_knockback[i]->Render(mdc);
		}
	}
	if (sequence == 2) {
		ExPlain3(mdc);

		const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();

		for (Missile* misile : missiles)
		{
			misile->Render(mdc);
			if (player[0]->boundingOnOff)
				misile->BoundingBox(mdc);
		}
	}




	

}

void Tutorial::ExPlain1(HDC mdc)
{
	// 공 그리기
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 192, 203)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	if (!_ballCollision[_cnt][0])
		Ellipse(mdc, pinkBall.left, pinkBall.top, pinkBall.right, pinkBall.bottom);

	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(80, 177, 223)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	if (!_ballCollision[_cnt][1])
		Ellipse(mdc, BlueBall.left, BlueBall.top, BlueBall.right, BlueBall.bottom);

	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);
	
	

	HFONT font, oldfont;
	{
		SetBkColor(mdc, RGB(0, 0, 0));
		SetTextColor(mdc, RGB(255, 0, 0));

		font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"궁서");
		oldfont = (HFONT)SelectObject(mdc, font);
		
		TCHAR lpOut[50];
		wsprintf(lpOut, L"TUTORIAL 1");
		RECT rect = { 100, 40, 1116, 150 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙



	}

	{
		SetTextColor(mdc, RGB(255, 255, 0));


		font = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);

		TCHAR lpOut[50];
		wsprintf(lpOut, L"Player1  A D F 를 이용하여 분홍공을 먹어보세요");
		RECT rect = { 100, 100, 1116, 210 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙

		wsprintf(lpOut, L" Player2  ← → J 를 이용하여 파란공을 먹어보세요");
		RECT rect2 = { 100, 150, 1116, 260 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙

	}

	SelectObject(mdc, oldfont);
	DeleteObject(font);
	DeleteObject(oldfont);

}

void Tutorial::ExPlain2(HDC mdc)
{
	// 공 그리기
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255, 192, 203)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	if (!_ballCollision[_cnt][0])
		Ellipse(mdc, pinkBall.left, pinkBall.top, pinkBall.right, pinkBall.bottom);

	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(80, 177, 223)); // GDI: 브러시 만들기
	oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

	if (!_ballCollision[_cnt][1])
		Ellipse(mdc, BlueBall.left, BlueBall.top, BlueBall.right, BlueBall.bottom);

	SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
	DeleteObject(hBrush);


	HFONT font, oldfont;

	{
		SetBkColor(mdc, RGB(0, 0, 0));
		SetTextColor(mdc, RGB(255, 0, 0));

		font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);

		TCHAR lpOut[50];
		wsprintf(lpOut, L"TUTORIAL 2");
		RECT rect = { 100, 40, 1116, 150 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙

	}

	{
		SetTextColor(mdc, RGB(255, 255, 0));


		font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);

		TCHAR lpOut[50];
		
		wsprintf(lpOut, L"PLAYER2  'K'를 눌러 상자를 밀어보세요");
		RECT rect2 = { 100, 130, 1116, 240 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙

		wsprintf(lpOut, L"가시에 닿으면 캐릭터가 넉백이 됩니다");
		rect2 = { 100, 180, 1116, 290 };

		DrawText(mdc, lpOut, _tcslen(lpOut), &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙


	}

	SelectObject(mdc, oldfont);
	DeleteObject(font);
	DeleteObject(oldfont);
}

void Tutorial::ExPlain3(HDC mdc)
{
	HFONT font, oldfont;

	{
		SetBkColor(mdc, RGB(0, 0, 0));
		SetTextColor(mdc, RGB(255, 0, 0));

		font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);

		TCHAR lpOut[50];
		wsprintf(lpOut, L"TUTORIAL 3");
		RECT rect = { 100, 40, 1116, 150 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙

	}

	{
		SetTextColor(mdc, RGB(255, 255, 0));


		font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);

		TCHAR lpOut[50];

		wsprintf(lpOut, L"Player1   'G' 를 눌러 플레이어 위치를 바꿔보세요");
		RECT rect2 = { 100, 130, 1116, 240 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙


	}

	SelectObject(mdc, oldfont);
	DeleteObject(font);
	DeleteObject(oldfont);

	const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	if (player[0]->GetCnt3() == 0) {
		font = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
			VARIABLE_PITCH | FF_ROMAN, L"맑은 고딕");
		oldfont = (HFONT)SelectObject(mdc, font);


		TCHAR lpOut[50];
		wsprintf(lpOut, L"고생하셨습니다!!!");
		RECT rect = { 100, 40, 1116, 150 };
		DrawText(mdc, lpOut, _tcslen(lpOut), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //--- 한 라인, 수직/수평 중앙


		SelectObject(mdc, oldfont);
		DeleteObject(font);
		DeleteObject(oldfont);
		--player[0]->GetCnt3();
	}
	else if (player[0]->GetCnt3() == -1) {
		this_thread::sleep_for(1000ms);
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::LOBBY);
	}
}

void Tutorial::BallCollision()
{
	const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
	TutorialPlayer* p = player[0];


	if (_ballCollision[_cnt][0] && _ballCollision[_cnt][1]) {

		if (_cnt == 0) {
			p->_posP1.x = 10;
			p->_posP2.x = 40;

			p->_posP1.y = 200;
			p->_posP2.y = 200;

			p->_motionP1 = Motion::RIGHT;
			p->_motionP2 = Motion::RIGHT;
			BlueBall.left = 1000;
			BlueBall.right = 1000 + 25;
			pinkBall.left = 1100;
			pinkBall.right = 1100 + 25;
		}
		else if (_cnt == 1) {
			p->_posP1.x = 50;
			p->_posP2.x = WINDOW_WIDTH - 100;

			p->_posP1.y = 200;
			p->_posP2.y = 200;
		}

		sequence = ++_cnt;

	}

	RECT intersect_rect{};
	RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
	RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
	
	if (IntersectRect(&intersect_rect, &p_rect, &pinkBall))
		_ballCollision[_cnt][0] = true;
	if (IntersectRect(&intersect_rect, &p2_rect, &BlueBall))
		_ballCollision[_cnt][1] = true;

}
