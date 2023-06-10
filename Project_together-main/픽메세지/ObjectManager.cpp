#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "BackGround.h"
#include "Tile_P1.h"
#include "Tile_P2.h"
#include "Tile.h"
#include "Tile_Moving.h"
#include "Tile_KnockBack.h"
#include "Tile_Push.h"
#include "Tile_dir.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Tile_KnockBack* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileKB.begin(), _vTileKB.end(), object);

	if (findit != _vTileKB.end())
		return;

	//////////////////////////////////////
	_vTileKB.push_back(object);

}

void ObjectManager::Add(Tile_Push* object)
{

	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_vTilePush.begin(), _vTilePush.end(), object);

	if (findit != _vTilePush.end())
		return;
	//////////////////////////////////////

	_vTilePush.push_back(object);


}

void ObjectManager::Add(Tile_bottom* object)
{


	if (object == nullptr) return;
	//객체 중복검사
	auto findit = std::find(_vTilebottom.begin(), _vTilebottom.end(), object);

	if (findit != _vTilebottom.end())
		return;
	//////////////////////////////////////

	_vTilebottom.push_back(object);
}

void ObjectManager::Add(Tile_END* object)
{

	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileending.begin(), _vTileending.end(), object);

	if (findit != _vTileending.end())
		return;
	//////////////////////////////////////

	_vTileending.push_back(object);
}

void ObjectManager::Add(Tile_Switch* object)
{

	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileSwitch.begin(), _vTileSwitch.end(), object);

	if (findit != _vTileSwitch.end())
		return;
	//////////////////////////////////////

	_vTileSwitch.push_back(object);
}

void ObjectManager::Add(TutorialPlayer* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_tutorial_player.begin(), _tutorial_player.end(), object);

	if (findit != _tutorial_player.end())
		return;
	//////////////////////////////////////

	_tutorial_player.push_back(object);

}

void ObjectManager::Add(TutorialBottom* object)
{

	{
		if (object == nullptr) return;

		//객체 중복검사
		auto findit = std::find(_tutorial_bottom.begin(), _tutorial_bottom.end(), object);

		if (findit != _tutorial_bottom.end())
			return;
		//////////////////////////////////////

		_tutorial_bottom.push_back(object);
	}
}

void ObjectManager::Add(Tile_dir* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vtileDir.begin(), _vtileDir.end(), object);

	if (findit != _vtileDir.end())
		return;
	//////////////////////////////////////

	_vtileDir.push_back(object);
}


void ObjectManager::Add(Tile_Climb* object)
{

	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileClimb.begin(), _vTileClimb.end(), object);

	if (findit != _vTileClimb.end())
		return;
	//////////////////////////////////////

	_vTileClimb.push_back(object);

}

void ObjectManager::Add(Monster* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_monster.begin(), _monster.end(), object);

	if (findit != _monster.end())
		return;
	//////////////////////////////////////

	_monster.push_back(object);
}

void ObjectManager::Add(Player* object)
{
	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_player.begin(), _player.end(), object);

	if (findit != _player.end())
		return;
	//////////////////////////////////////

	_player.push_back(object);
}

void ObjectManager::Add(BackGround* object)
{
	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_bg.begin(), _bg.end(), object);

	if (findit != _bg.end())
		return;
	//////////////////////////////////////

	_bg.push_back(object);
}

void ObjectManager::Add(Tile* object)
{

	if (object == nullptr) return;


	//객체 중복검사
	auto findit = std::find(_vTile.begin(), _vTile.end(), object);

	if (findit != _vTile.end())
		return;
	//////////////////////////////////////

	_vTile.push_back(object);


}


void ObjectManager::Add(Missile* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vmissile.begin(), _vmissile.end(), object);

	if (findit != _vmissile.end())
		return;

	//////////////////////////////////////
	_vmissile.push_back(object);
}

void ObjectManager::Add(Tile_P1* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileP1.begin(), _vTileP1.end(), object);

	if (findit != _vTileP1.end())
		return;
	//////////////////////////////////////
	_vTileP1.push_back(object);
}

void ObjectManager::Add(Tile_P2* object)
{
	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileP2.begin(), _vTileP2.end(), object);

	if (findit != _vTileP2.end())
		return;
	//////////////////////////////////////
	_vTileP2.push_back(object);

}

void ObjectManager::Add(Tile_Moving* object)
{

	if (object == nullptr) return;

	//객체 중복검사
	auto findit = std::find(_vTileMove.begin(), _vTileMove.end(), object);

	if (findit != _vTileMove.end())
		return;
	//////////////////////////////////////
	_vTileMove.push_back(object);

}

//======================================================================================//


void ObjectManager::Remove(Tile_bottom* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTilebottom.begin(), _vTilebottom.end(), object);

	_vTilebottom.erase(it, _vTilebottom.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;


}

void ObjectManager::Remove(Tile_END* object)
{

	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileending.begin(), _vTileending.end(), object);

	_vTileending.erase(it, _vTileending.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;



}

void ObjectManager::Remove(Tile_Switch* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileSwitch.begin(), _vTileSwitch.end(), object);

	_vTileSwitch.erase(it, _vTileSwitch.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(TutorialPlayer* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_tutorial_player.begin(), _tutorial_player.end(), object);

	_tutorial_player.erase(it, _tutorial_player.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(TutorialBottom* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_tutorial_bottom.begin(), _tutorial_bottom.end(), object);

	_tutorial_bottom.erase(it, _tutorial_bottom.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile_dir* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vtileDir.begin(), _vtileDir.end(), object);

	_vtileDir.erase(it, _vtileDir.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}




void ObjectManager::Remove(Tile_KnockBack* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileKB.begin(), _vTileKB.end(), object);

	_vTileKB.erase(it, _vTileKB.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile_Push* object)
{

	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTilePush.begin(), _vTilePush.end(), object);

	_vTilePush.erase(it, _vTilePush.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;


}

void ObjectManager::Remove(Tile_Climb* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileClimb.begin(), _vTileClimb.end(), object);

	_vTileClimb.erase(it, _vTileClimb.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;

}

void ObjectManager::Remove(Monster* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_monster.begin(), _monster.end(), object);

	_monster.erase(it, _monster.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Player* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_player.begin(), _player.end(), object);

	_player.erase(it, _player.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(BackGround* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_bg.begin(), _bg.end(), object);

	_bg.erase(it, _bg.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTile.begin(), _vTile.end(), object);

	_vTile.erase(it, _vTile.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;

}


void ObjectManager::Remove(Missile* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vmissile.begin(), _vmissile.end(), object);

	_vmissile.erase(it, _vmissile.end());
	//////////////////////////////////////////
	//메모리 삭제
	delete object;

}


void ObjectManager::Remove(Tile_P1* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileP1.begin(), _vTileP1.end(), object);

	_vTileP1.erase(it, _vTileP1.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;
}

void ObjectManager::Remove(Tile_P2* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileP2.begin(), _vTileP2.end(), object);

	_vTileP2.erase(it, _vTileP2.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;


}

void ObjectManager::Remove(Tile_Moving* object)
{
	if (object == nullptr)
		return;

	//벡터내에서 삭제//////////////////////////////
	auto it = std::remove(_vTileMove.begin(), _vTileMove.end(), object);

	_vTileMove.erase(it, _vTileMove.end());
	//////////////////////////////////////////

	//메모리 삭제
	delete object;
}

void ObjectManager::Clear()
{
	//벡터내에 모든 메모리삭제
	std::for_each(_player.begin(), _player.end(), [=](Player* obj) {delete obj; });
	std::for_each(_bg.begin(), _bg.end(), [=](BackGround* obj) {delete obj; });
	std::for_each(_vTile.begin(), _vTile.end(), [=](Tile* obj) {delete obj; });
	std::for_each(_vTileP1.begin(), _vTileP1.end(), [=](Tile_P1* obj) {delete obj; });
	std::for_each(_vTileP2.begin(), _vTileP2.end(), [=](Tile_P2* obj) {delete obj; });
	std::for_each(_vTileKB.begin(), _vTileKB.end(), [=](Tile_KnockBack* obj) {delete obj; });
	std::for_each(_vTileMove.begin(), _vTileMove.end(), [=](Tile_Moving* obj) {delete obj; });
	std::for_each(_vmissile.begin(), _vmissile.end(), [=](Missile* obj) {delete obj; });
	std::for_each(_vTilePush.begin(), _vTilePush.end(), [=](Tile_Push* obj) {delete obj; });
	std::for_each(_vTileClimb.begin(), _vTileClimb.end(), [=](Tile_Climb* obj) {delete obj; });
	std::for_each(_monster.begin(), _monster.end(), [=](Monster* obj) {delete obj; });
	std::for_each(_vTilebottom.begin(), _vTilebottom.end(), [=](Tile_bottom* obj) {delete obj; });
	std::for_each(_vTileending.begin(), _vTileending.end(), [=](Tile_END* obj) {delete obj; });
	std::for_each(_vTileSwitch.begin(), _vTileSwitch.end(), [=](Tile_Switch* obj) {delete obj; });
	std::for_each(_tutorial_player.begin(), _tutorial_player.end(), [=](TutorialPlayer* obj) {delete obj; });
	std::for_each(_tutorial_bottom.begin(), _tutorial_bottom.end(), [=](TutorialBottom* obj) {delete obj; });
	std::for_each(_vtileDir.begin(), _vtileDir.end(), [=](Tile_dir* obj) {delete obj; });


	//벡터 비우기
	_player.clear();
	_bg.clear();
	_vTile.clear();
	_vTileP1.clear();
	_vTileP2.clear();
	_vTileKB.clear();
	_vTileMove.clear();
	_vmissile.clear();
	_vTilePush.clear();
	_vTileClimb.clear();
	_monster.clear();
	_vTilebottom.clear();
	_vTileending.clear();
	_vTileSwitch.clear();
	_tutorial_player.clear();
	_tutorial_bottom.clear();
	_vtileDir.clear();
}


//컨테이너벨트
//점프도와주는발판
//바이킹낫
//새