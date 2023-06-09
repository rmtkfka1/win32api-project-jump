#pragma once
#define DECLARE_SINGLE(classname)                   \
public:											    \
	classname(){}									\
													\
public:												\
													\
	static classname* GetInstance()					\
	{												\
		static classname s_Insatance;				\
		return &s_Insatance;						\
	}												

#define GET_SINGLE(classname) classname::GetInstance() 

#define WINDOW_WIDTH 1216
#define WINDOW_HEIGHT 639


#define MakeTile(X,Y) do {											     \
    Tile* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile>();       \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)



#define MakeTile_P1(X,Y) do {											\
    Tile_P1* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P1>(); \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)


#define MakeTile_P2(X,Y) do {											\
    Tile_P2* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_P2>(); \
    tile->SetPos(Pos(X, Y));											\
    tile->Init();														\
    GET_SINGLE(ObjectManager)->Add(tile);								\
} while(0)
          

#define MakeTile_Moving(X,Y) do {											          \
   Tile_Moving* moving_tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Moving>(); \
   moving_tile->SetPos(Pos(X, Y));									                  \
   moving_tile->Init();													              \
   GET_SINGLE(ObjectManager)->Add(moving_tile);								          \
} while(0)


#define MakeTile_KnocBack(X,Y) do {											    \
    Tile_KnockBack* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_KnockBack>(); \
    tile->SetPos(Pos(X, Y));											    \
    tile->Init();														    \
    GET_SINGLE(ObjectManager)->Add(tile);								    \
} while(0)

#define MakeTile_PUSH(X,Y) do {											       \
    Tile_Push* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Push>();    \
    tile->SetPos(Pos(X, Y));											       \
    tile->Init();														       \
    GET_SINGLE(ObjectManager)->Add(tile);								       \
} while(0)


#define MakeTile_Climb(X,Y) do {											       \
    Tile_Climb* tile = GET_SINGLE(ObjectManager)->CreateObject<Tile_Climb>();    \
    tile->SetPos(Pos(X, Y));											       \
    tile->Init();														       \
    GET_SINGLE(ObjectManager)->Add(tile);								       \
} while(0)