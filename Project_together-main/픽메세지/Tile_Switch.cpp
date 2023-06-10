#include "pch.h"
#include "Tile_Switch.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "Tile_P1.h"
#include "Tile_P2.h"


Tile_Switch::Tile_Switch() :Object(ObjectType::TILE)
{


}


Tile_Switch::~Tile_Switch()
{
    tile_img.Destroy();

}

void Tile_Switch::Init()
{
    tile_img.Load(L"리소스\\스위치수정.png");

    size.x = 30;
    size.y = 30;

}

void Tile_Switch::Update()
{
    {
        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

        Player* p = player[0];

        const vector<Tile*>& tiles = GET_SINGLE(ObjectManager)->GetTile();   //벡터를 가져오는것

        RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
        RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
            , _pos.y + size.y };
        RECT intersect_rect;


        if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
        {
            TURNON = TRUE;
        }
        else
        {
            TURNON = FALSE;
        }

    }

}

void Tile_Switch::Render(HDC mdc)
{


    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];

    Pos diff = p->GetDiffP1();
    Pos diff2 = p->GetDiffP2();

    if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
        _Renderpos = _pos - diff;                // << player1일 때
    else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
        _Renderpos = _pos - diff2;                // << player2일 때


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

void Tile_Switch::BoundingBox(HDC mdc) {
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