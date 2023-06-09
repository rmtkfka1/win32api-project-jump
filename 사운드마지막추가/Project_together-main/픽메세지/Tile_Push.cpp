
#include "pch.h"
#include "Tile_Push.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "SceanManager.h"

Tile_Push::Tile_Push() :Object(ObjectType::TILE)
{


}


Tile_Push::~Tile_Push()
{
    tile_img.Destroy();
}

void Tile_Push::Init()
{
    tile_img.Load(L"리소스\\Tile_Push.png");

    size.x = 50;
    size.y = 50;
}

void Tile_Push::Update()
{
    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
    Player* p = player[0];

    RECT p_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
    RECT p_rect2 = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };

    RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
        , _pos.y + size.y };
    RECT intersect_rect;
    // PLAYER2

    if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
    {

        p->pushBool = true;



        float GapW = intersect_rect.right - intersect_rect.left;
        float GAPH = intersect_rect.bottom - intersect_rect.top;

        if (GapW > GAPH)
        {

            if (intersect_rect.top == tile_rect.top)
            {
                p->_posP2.y -= GAPH;
                p->landing2 = true;
                p->fallP2 = false;
            }

            else if (intersect_rect.bottom == tile_rect.bottom)
            {
                p->_posP2.y += GAPH;
            }
        }

        else
        {
            if (intersect_rect.left == tile_rect.left)
            {
                p->_posP2.x = p->_posP2.x - GapW;
            }

            else if (intersect_rect.right == tile_rect.right)
            {
                p->_posP2.x = p->_posP2.x + GapW;

            }
        }

        if (p->realpushBool && p->_posP2.x) 
        {
            if (p->_motionP2 == Motion::RIGHT)
                _pos.x += 1.f;
            else if (p->_motionP2 == Motion::LEFT)
                _pos.x -= 1.f;
        }






    }

   
    if (IntersectRect(&intersect_rect, &p_rect2, &tile_rect))
    {
    

        float GapW = intersect_rect.right - intersect_rect.left;
        float GAPH = intersect_rect.bottom - intersect_rect.top;

        if (GapW > GAPH)
        {

            if (intersect_rect.top == tile_rect.top)
            {
                p->_posP1.y -= GAPH;
                p->landing1 = true;
                p->fallP1 = false;
            }

            else if (intersect_rect.bottom == tile_rect.bottom)
            {
                p->_posP1.y += GAPH;
            }
        }

        else
        {
            if (intersect_rect.left == tile_rect.left)
            {
                p->_posP1.x = p->_posP1.x - GapW;
            }

            else if (intersect_rect.right == tile_rect.right)
            {
                p->_posP1.x = p->_posP1.x + GapW;

            }
        }

      

    }
}

void Tile_Push::Render(HDC mdc)
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


void Tile_Push::BoundingBox(HDC mdc) {

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