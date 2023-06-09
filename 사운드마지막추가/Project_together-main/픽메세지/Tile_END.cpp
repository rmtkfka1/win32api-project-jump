#include "pch.h"
#include "Tile_END.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "SceanManager.h"

Tile_END::Tile_END() :Object(ObjectType::TILE)
{


}


Tile_END::~Tile_END()
{
    tile_img.Destroy();
}

void Tile_END::Init()
{
    tile_img.Load(L"리소스\\door.png");

    size.x = 40;
    size.y = 40;
}

void Tile_END::Update()
{

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
    Player* p = player[0];

    RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
    RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
    RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
        , _pos.y + size.y };
    RECT intersect_rect;


    if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
    {

        if (IntersectRect(&intersect_rect, &p2_rect, &tile_rect))
        {
            GET_SINGLE(SceneManager)->ChangeScene(SceneType::END);
        }
        
    }

}

void Tile_END::Render(HDC mdc)
{
    mdc2 = CreateCompatibleDC(mdc);
    hBitmap2 = CreateCompatibleBitmap(mdc, tile_img.GetWidth(), tile_img.GetHeight());
    SelectObject(mdc2, (HBITMAP)hBitmap2);

    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];

    Pos diff = p->GetDiffP1();
    Pos diff2 = p->GetDiffP2();

    if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
        _Renderpos = _pos - diff;                // << player1일 때
    else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
        _Renderpos = _pos - diff2;                // << player2일 때

    TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x, size.y,
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));

    DeleteObject(hBitmap2);
    DeleteDC(mdc2);
}

void Tile_END::BoundingBox(HDC mdc)
{
}
