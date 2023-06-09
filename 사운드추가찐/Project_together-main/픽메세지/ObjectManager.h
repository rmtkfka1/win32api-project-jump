#pragma once
#pragma once

class Object;
class Player;
class BackGround;
class Missile;
class Tile;
class Tile_P1;
class Tile_P2;
class Tile_Moving;
class Tile_KnockBack;
class Tile_Push;
class Tile_Climb;
class Monster;
class Tile_bottom;
class Tile_END;
class Tile_Switch;


class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	~ObjectManager();

	void Add(Player* object);
	void Add(BackGround* object);
	void Add(Tile* object);
	void Add(Tile_P1* object);
	void Add(Tile_P2* object);
	void Add(Tile_Moving* object);
	void Add(Missile* object);
	void Add(Tile_KnockBack* object);
	void Add(Tile_Push* object);
	void Add(Tile_Climb* object);
	void Add(Monster* object);
	void Add(Tile_bottom* object);
	void Add(Tile_END* object);
	void Add(Tile_Switch* object);

	void Remove(Player* object);
	void Remove(BackGround* object);
	void Remove(Tile* object);
	void Remove(Tile_P1* object);
	void Remove(Tile_P2* object);
	void Remove(Tile_Moving* object);
	void Remove(Missile* object);
	void Remove(Tile_KnockBack* object);
	void Remove(Tile_Push* object);
	void Remove(Tile_Climb* object);
	void Remove(Monster* object);
	void Remove(Tile_bottom* object);
	void Remove(Tile_END* object);
	void Remove(Tile_Switch* object);

	void Clear(); //씬전환되면 동적할당된 메모리싹날라기

	const vector<Player*>& GetPlayer() { return _player; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<BackGround*>& GetBackGround() { return _bg; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile*>&    GetTile() { return _vTile; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_P1*>& GetTile_P1() { return _vTileP1; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_P2*>& GetTile_P2() { return _vTileP2; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_KnockBack*>& GetKnockBack() { return _vTileKB; }
	const vector<Tile_Moving*>& GetTile_Moving() { return _vTileMove; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Missile*>& GetMissile() { return _vmissile; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_Push*>& GetTilePush() { return _vTilePush; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_Climb*>& GetTileClimb() { return _vTileClimb; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Monster*>& GetMonster() { return _monster; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_bottom*>& GetTilebottom() { return _vTilebottom; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_END*>& GetTileending() { return _vTileending; } //외부 CPP,헤더파일에서 벡터가져오기//
	const vector<Tile_Switch*>& GetTilSwitch() { return _vTileSwitch; } //외부 CPP,헤더파일에서 벡터가져오기//


	template<typename T>
	T* CreateObject()
	{
		T* object = new T();


		return object;
	}

private:

	vector<Player*> _player;
	vector<BackGround*> _bg;
	vector<Tile*> _vTile;
	vector<Tile_P1*> _vTileP1;
	vector<Tile_P2*> _vTileP2;
	vector<Tile_Moving*> _vTileMove;
	vector<Missile*> _vmissile;
	vector<Tile_KnockBack*> _vTileKB;
	vector<Tile_Push*> _vTilePush;
	vector<Tile_Climb*> _vTileClimb;
	vector<Monster*> _monster;
	vector<Tile_bottom*> _vTilebottom;
	vector<Tile_END*> _vTileending;
	vector<Tile_Switch*> _vTileSwitch;
};

