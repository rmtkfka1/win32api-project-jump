#include "pch.h"
#include "Stage1.h"
#include "TimeManager.h"
#include "BackGround.h"
#include "KeyManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Misile.h"
#include "Tile_P1.h"
#include "Tile_P2.h"
#include "Tile.h"
#include "Tile_Moving.h"
#include "Tile_KnockBack.h"
#include "Tile_Push.h"
#include "Tile_Climb.h"
#include "Monster.h"
#include "Tile_bottom.h"
#include "Tile_END.h"
#include "Tile_Switch.h"
#include "Tile_dir.h"


Stage1::~Stage1()
{
	GET_SINGLE(ObjectManager)->Clear();
}

void Stage1::Init()
{


	BackGround* bg = GET_SINGLE(ObjectManager)->CreateObject<BackGround>();
	bg->Init();
	GET_SINGLE(ObjectManager)->Add(bg);

	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	player->Init(bg);
	GET_SINGLE(ObjectManager)->Add(player);
	//===============================TILE _DIR==============================//	







	{

		Tile_dir* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_dir>();
		tile->SetPos(Pos(2200, -500));
		tile->Init();
		tile->SetSize(Pos(60, 60));
		GET_SINGLE(ObjectManager)->Add(tile);
	}




	//============================ Tile  만들기 ==============================//

	//사이즈세팅을 위해 매크로안썼음

	Tile_bottom* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_bottom>();
	tile->SetPos(Pos(0, 439 + 32));
	tile->Init();
	tile->SetSize(Pos(4000, 200));
	GET_SINGLE(ObjectManager)->Add(tile);


	Tile_bottom* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile_bottom>();
	tile2->SetPos(Pos(3400, -2000));
	tile2->Init();
	tile2->SetSize(Pos(700, 3000));
	GET_SINGLE(ObjectManager)->Add(tile2);


	for (int i = 0; i < 5; ++i)
	{
		MakeTile(2600 + (i + 1) * 100, 70 - (i * 100));
	}


	{
		Tile* tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile2->SetPos(Pos(2600, 170));
		tile2->Init();
		tile2->SetSize(Pos(70, 40));
		GET_SINGLE(ObjectManager)->Add(tile2);
	}


	//끝에티어나온거
	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(3320, -400));
		tile->Init();
		tile->SetSize(Pos(80, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2600, -400));
		tile->Init();
		tile->SetSize(Pos(80, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}


	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2450, -400));
		tile->Init();
		tile->SetSize(Pos(50, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2300, -520));
		tile->Init();
		tile->SetSize(Pos(50, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}



	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(2100, 0));
		tile->Init();
		tile->SetSize(Pos(200, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	//vv
	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(1120, 0));
		tile->Init();
		tile->SetSize(Pos(150, 50));
		GET_SINGLE(ObjectManager)->Add(tile);

	}


	//v
	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(1650, 0));
		tile->Init();
		tile->SetSize(Pos(150, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}


	//사다리꼭다리
	MakeTile(840, -820);

	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(1900, -900));
		tile->Init();
		tile->SetSize(Pos(150, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}



	//끝에사다리 타일
	{
		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(700, 0));
		tile->Init();
		tile->SetSize(Pos(300, 50));
		GET_SINGLE(ObjectManager)->Add(tile);

	}


	{

		Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();
		tile->SetPos(Pos(3200, -920));
		tile->Init();
		tile->SetSize(Pos(200, 50));
		GET_SINGLE(ObjectManager)->Add(tile);
	}




	//=============================Tile_Switch 만들기 ///////////////////////

	{
		Tile_Switch* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Switch>();
		tile->SetPos(Pos(1900 + 75, -920));
		tile->Init();
		tile->SetSize(Pos(20, 20));
		GET_SINGLE(ObjectManager)->Add(tile);
	}


	{
		Tile_Switch* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Switch>();
		tile->SetPos(Pos(3240, -940));
		tile->Init();
		tile->SetSize(Pos(20, 20));
		GET_SINGLE(ObjectManager)->Add(tile);
	}

	//============================ Tile_P1 만들기 ==============================//
	{

		MakeTile_P1(3200, -520);

		MakeTile_P1(3100, -520);

		MakeTile_P1(3000, -520);


		MakeTile_P1(2800, -520);


		MakeTile_P1(2750, -320);

		MakeTile_P1(1950, 0);


	}
	//============================ Tile_P2 만들기 ==============================//
	{

		{
			Tile_P2* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P2>();
			tile->SetPos(Pos(2100, -1000));
			tile->Init();
			tile->SetSize(Pos(300, 20));
			GET_SINGLE(ObjectManager)->Add(tile);
		}

		{
			Tile_P2* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P2>();
			tile->SetPos(Pos(2500, -1100));
			tile->Init();
			tile->SetSize(Pos(50, 20));
			GET_SINGLE(ObjectManager)->Add(tile);
		}


		{
			Tile_P2* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P2>();
			tile->SetPos(Pos(2700, -1100));
			tile->Init();
			tile->SetSize(Pos(400, 20));
			GET_SINGLE(ObjectManager)->Add(tile);
		}







	}

	//============================ Moving_Tile 만들기  ===========================//

	{
		Tile_Moving* moving_tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile->Init();
		moving_tile->_move_range = Pos(0, 150);
		moving_tile->_DoyouWant_UP = true;
		moving_tile->_isMovingUp = false;
		moving_tile->_stat.speed = 2;
		moving_tile->SetPos(Pos(3100, 120));
		GET_SINGLE(ObjectManager)->Add(moving_tile);

	}

	{
		Tile_Moving* moving_tile2 = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile2->Init();
		moving_tile2->_move_range = Pos(300, 0);
		moving_tile2->_stat.speed = 1;
		moving_tile2->_DoyouWant_UP = false;
		moving_tile2->SetSize(Pos(50, 40));
		moving_tile2->SetPos(Pos(3000, 170));
		GET_SINGLE(ObjectManager)->Add(moving_tile2);
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	{
		Tile_Moving* moving_tile3 = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile3->Init();
		moving_tile3->_move_range = Pos(0, 150);
		moving_tile3->_DoyouWant_UP = true;
		moving_tile3->_isMovingUp = true;
		moving_tile3->SetSize(Pos(100, 40));
		moving_tile3->SetPos(Pos(900, -600));
		GET_SINGLE(ObjectManager)->Add(moving_tile3);
	}

	{
		Tile_Moving* moving_tile3 = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile3->Init();
		moving_tile3->_move_range = Pos(0, 200);
		moving_tile3->_stat.speed = 3;
		moving_tile3->_DoyouWant_UP = true;
		moving_tile3->_isMovingUp = true;
		moving_tile3->SetSize(Pos(100, 40));
		moving_tile3->SetPos(Pos(1250, -450));
		GET_SINGLE(ObjectManager)->Add(moving_tile3);
	}

	{
		Tile_Moving* moving_tile3 = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>();
		moving_tile3->Init();
		moving_tile3->_move_range = Pos(0, 150);
		moving_tile3->_stat.speed = 5;
		moving_tile3->_DoyouWant_UP = true;
		moving_tile3->_isMovingUp = true;
		moving_tile3->SetSize(Pos(100, 40));
		moving_tile3->SetPos(Pos(1600, -400));
		GET_SINGLE(ObjectManager)->Add(moving_tile3);
	}






	//============================ 넉백 타일 만들기 ==============================//
	{


		{
			Tile_KnockBack* tile_knockback = GET_SINGLE(ObjectManager)->CreateObject<Tile_KnockBack>();
			tile_knockback->Init();

			tile_knockback->SetSize(Pos(110, 130));
			tile_knockback->SetPos(Pos(1600, 370));
			GET_SINGLE(ObjectManager)->Add(tile_knockback);
		}






		////
		MakeTile_KnocBack(2200, -20);




		/// <summary>
		/// 
		/// </summary>
		MakeTile_KnocBack(2760, -1140);
		MakeTile_KnocBack(2880, -1140);
		MakeTile_KnocBack(3000, -1140);
	}





	//===============================Tile_Push(밀수있는 타일)만들기======================================//


	MakeTile_PUSH(1300, 430);
	/*MakeTile_PUSH(1000, 380);
	MakeTile_PUSH(1000, 330);
	MakeTile_PUSH(1000, 280);
	MakeTile_PUSH(1000, 230);*/
	////////////////////////


	MakeTile_PUSH(1600, -200);
	MakeTile_PUSH(1620, -150);
	MakeTile_PUSH(1640, -100);
	MakeTile_PUSH(1660, -50);




	//=====================================Tile_Climb(밧줄만들기) =====================================//

	MakeTile_Climb(850, -800);



	//=====================================Monster(몬스터 만들기) =====================================//


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(100, 200);
		monster1->_DoyouWant_UP = false;
		monster1->_stat.speed = 6;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(2600, -1080));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = false;
		monster1->_stat.speed = 6;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(2350, -1190));
		GET_SINGLE(ObjectManager)->Add(monster1);

	}

	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = false;
		monster1->_stat.speed = 6;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(1900, -1190));
		GET_SINGLE(ObjectManager)->Add(monster1);

	}




	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(900, -200));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}

	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(100, 100);
		monster1->_DoyouWant_UP = false;
		monster1->SetSize(Pos(20, 20));
		monster1->_stat.speed = 3;
		monster1->SetPos(Pos(1000, -300));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(100, 100);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = true;
		monster1->SetSize(Pos(20, 20));
		monster1->_stat.speed = 3;
		monster1->SetPos(Pos(1100, -300));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}



	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(900, -400));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = false;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(750, -600));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(200, 200);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = false;
		monster1->SetSize(Pos(20, 20));
		monster1->SetPos(Pos(750, -400));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}



	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(120, 100);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = true;
		monster1->SetSize(Pos(20, 20));
		monster1->_stat.speed = 3;
		monster1->SetPos(Pos(1000, -600));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}


	{

		Monster* monster1 = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster1->Init();
		monster1->_move_range = Pos(120, 100);
		monster1->_DoyouWant_UP = false;
		monster1->_isMovingLeft = false;
		monster1->SetSize(Pos(20, 20));
		monster1->_stat.speed = 3;
		monster1->SetPos(Pos(800, -600));
		GET_SINGLE(ObjectManager)->Add(monster1);
	}

	//=====================================ENDING 타일만들기 ////////////////////////////////////////////////////////

	{
		Tile_END* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_END>();
		tile->SetPos(Pos(3350, -960));
		tile->Init();
		tile->SetSize(Pos(40, 40));
		GET_SINGLE(ObjectManager)->Add(tile);

	}


}

void Stage1::Update()
{

	const vector<BackGround*>& bg = GET_SINGLE(ObjectManager)->GetBackGround();
	bg[0]->Update();

	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();
	player[0]->Update();


	const vector<Tile_Switch*> tile_switch = GET_SINGLE(ObjectManager)->GetTilSwitch();
	for (int i = 0; i < tile_switch.size(); ++i)
	{
		tile_switch[i]->Update();
	}

	const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();
	for (int i = 0; i < missiles.size(); ++i)
	{
		missiles[i]->Update();
	}


	const vector<Tile*> tiles = GET_SINGLE(ObjectManager)->GetTile();
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Update();
	}



	const vector<Tile_P1*> tiles_p1 = GET_SINGLE(ObjectManager)->GetTile_P1();
	for (int i = 0; i < tiles_p1.size(); ++i)
	{
		tiles_p1[i]->Update();
	}

	if (tile_switch.size() != 0) {
		if (tile_switch[0]->TURNON || tile_switch[1]->TURNON) {
			const vector<Tile_P2*> tiles_p2 = GET_SINGLE(ObjectManager)->GetTile_P2();
			for (int i = 0; i < tiles_p2.size(); ++i)
			{
				tiles_p2[i]->Update();
			}
		}

	}



	const vector<Tile_Moving*> moving_tile = GET_SINGLE(ObjectManager)->GetTile_Moving();
	for (int i = 0; i < moving_tile.size(); ++i)
	{
		moving_tile[i]->Update();
	}

	const vector<Tile_KnockBack*> tiles_KnockBack = GET_SINGLE(ObjectManager)->GetKnockBack();
	for (int i = 0; i < tiles_KnockBack.size(); ++i)
	{
		tiles_KnockBack[i]->Update();
	}


	const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
	for (int i = 0; i < tile_push.size(); ++i)
	{
		tile_push[i]->Update();
	}

	const vector<Tile_Climb*> tile_climb = GET_SINGLE(ObjectManager)->GetTileClimb();
	for (int i = 0; i < tile_climb.size(); ++i)
	{
		tile_climb[i]->Update();
	}

	const vector<Monster*> monster = GET_SINGLE(ObjectManager)->GetMonster();
	for (int i = 0; i < monster.size(); ++i)
	{
		monster[i]->Update();
	}


	const vector<Tile_bottom*> tile_bottom = GET_SINGLE(ObjectManager)->GetTilebottom();
	for (int i = 0; i < tile_bottom.size(); ++i)
	{
		tile_bottom[i]->Update();
	}

	const vector<Tile_END*> tile_End = GET_SINGLE(ObjectManager)->GetTileending();
	for (int i = 0; i < tile_End.size(); ++i)
	{
		tile_End[i]->Update();
	}





};


void Stage1::Render(HDC mdc)
{
	const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();

	const vector<BackGround*>& bg = GET_SINGLE(ObjectManager)->GetBackGround();

	bg[0]->Render(mdc, player[0]->GetDiffP1(), player[0]->GetDiffP2(), player[0]->GetTurn(), player[0]->GetDivide());



	const vector<Tile_END*> tile_End = GET_SINGLE(ObjectManager)->GetTileending();
	for (int i = 0; i < tile_End.size(); ++i)
	{
		tile_End[i]->Render(mdc);
	}


	const vector<Tile*> tiles = GET_SINGLE(ObjectManager)->GetTile();
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Render(mdc);
		if (player[0]->boundingOnOff)
			tiles[i]->BoundingBox(mdc);

	}


	const vector<Tile_P1*> tiles_p1 = GET_SINGLE(ObjectManager)->GetTile_P1();
	for (Tile_P1* tile : tiles_p1)
	{
		tile->Render(mdc);
		if (player[0]->boundingOnOff)
			tile->BoundingBox(mdc);
	}

	const vector<Tile_Switch*> tile_switch = GET_SINGLE(ObjectManager)->GetTilSwitch();
	for (int i = 0; i < tile_switch.size(); ++i)
	{
		tile_switch[i]->Render(mdc);
	}



	if (tile_switch[0]->TURNON || tile_switch[1]->TURNON)
	{
		const vector<Tile_P2*> tiles_p2 = GET_SINGLE(ObjectManager)->GetTile_P2();
		for (Tile_P2* tile : tiles_p2)
		{
			tile->Render(mdc);
			if (player[0]->boundingOnOff)
				tile->BoundingBox(mdc);
		}
	}


	const vector<Missile*>& missiles = GET_SINGLE(ObjectManager)->GetMissile();

	for (Missile* misile : missiles)
	{
		misile->Render(mdc);
		if (player[0]->boundingOnOff)
			misile->BoundingBox(mdc);
	}


	const vector<Tile_Moving*> moving_tile = GET_SINGLE(ObjectManager)->GetTile_Moving();
	for (int i = 0; i < moving_tile.size(); ++i)
	{
		moving_tile[i]->Render(mdc);
		if (player[0]->boundingOnOff)
			moving_tile[i]->BoundingBox(mdc);
	}

	const vector<Tile_KnockBack*> tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();
	for (Tile_KnockBack* tile : tiles_knockback)
	{
		tile->Render(mdc);
		if (player[0]->boundingOnOff)
			tile->BoundingBox(mdc);
	}


	const vector<Tile_Push*> tile_push = GET_SINGLE(ObjectManager)->GetTilePush();
	for (int i = 0; i < tile_push.size(); ++i)
	{
		tile_push[i]->Render(mdc);
		if (player[0]->boundingOnOff)
			tile_push[i]->BoundingBox(mdc);
	}


	const vector<Tile_Climb*> tile_climb = GET_SINGLE(ObjectManager)->GetTileClimb();
	for (int i = 0; i < tile_climb.size(); ++i)
	{
		tile_climb[i]->Render(mdc);
		if (player[0]->boundingOnOff)
			tile_climb[i]->BoundingBox(mdc);
	}

	const vector<Monster*> monster = GET_SINGLE(ObjectManager)->GetMonster();
	for (int i = 0; i < monster.size(); ++i)
	{
		monster[i]->Render(mdc);
		if (player[0]->boundingOnOff)
			monster[i]->BoundingBox(mdc);
	}

	player[0]->Render(mdc);
	if (player[0]->boundingOnOff)
		player[0]->BoundingBox(mdc);



	const vector<Tile_bottom*> tile_bottom = GET_SINGLE(ObjectManager)->GetTilebottom();
	for (int i = 0; i < tile_bottom.size(); ++i)
	{
		tile_bottom[i]->Render(mdc);
	}


	const vector<Tile_dir*> TT = GET_SINGLE(ObjectManager)->GetTileDir();
	for (int i = 0; i < TT.size(); ++i)
	{
		TT[i]->Render(mdc);
	}

}