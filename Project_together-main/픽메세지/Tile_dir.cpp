#include "pch.h"
#include "Tile_dir.h"
#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "Tile_P1.h"
#include "Tile_P2.h"


Tile_dir::Tile_dir() :Object(ObjectType::TILE)
{


}


Tile_dir::~Tile_dir()
{
    tile_img.Destroy();

}

void Tile_dir::Init()
{
    tile_img.Load(L"���ҽ�\\ȭ��ǥ.png");


    size.x = 50;
    size.y = 50;


}

void Tile_dir::Update()
{
   

}

void Tile_dir::Render(HDC mdc)
{

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //���͸� ��������

    Player* p = player[0];


    Pos diff = p->GetDiffP1();
    Pos diff2 = p->GetDiffP2();

    if (p->_turn == ObjectType::PLAYER1)            // ������ 1�� ��
        _Renderpos = _pos - diff;                // << player1�� ��
    else if (p->_turn == ObjectType::PLAYER2)        // ������ 2
        _Renderpos = _pos - diff2;                // << player2�� ��


    hBitmap2 = CreateCompatibleBitmap(mdc, tile_img.GetWidth(), tile_img.GetHeight());
    mdc2 = CreateCompatibleDC(mdc);
    SelectObject(mdc2, (HBRUSH)hBitmap2);


    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());


    TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x, size.y,
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));

    DeleteDC(mdc2);
    DeleteObject(hBitmap2);


}

void Tile_dir::BoundingBox(HDC mdc)
{
   
}