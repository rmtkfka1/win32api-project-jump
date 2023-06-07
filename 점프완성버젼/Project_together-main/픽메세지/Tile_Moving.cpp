#include "pch.h"
#include "Tile_Moving.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "Tile_P1.h"
#include "Tile_P2.h"


Tile_Moving::Tile_Moving() :Object(ObjectType::TILE)
{


}


Tile_Moving::~Tile_Moving()
{

    tile_img.Destroy();
}

void Tile_Moving::Init()
{
    tile_img.Load(L"���ҽ�\\moving_tile.png");

    size.x = 40;
    size.y = 30;

    _move_range = Pos(200, 200);
    _stat.speed = 1;
    //_first_move_renge = _move_range;
    _isMovingUp = false; 
    _isMovingLeft = true;
    _DoyouWant_UP = true;
}

void Tile_Moving::Update()
{


    if (_DoyouWant_UP)
    {
        {

            static int counting = 0;
            if (_isMovingUp)
            {
                counting++;
                _pos.y -= 2;

                if (counting == _move_range.y / 2)
                {
                    counting = 0;
                    _isMovingUp = false;
                }
            }
            else
            {
                counting++;
                _pos.y += 2;
                if (counting == _move_range.y / 2)
                {
                    counting = 0;
                    _isMovingUp = true;
                }

            }
        }
    }

    else
    {
        {
            static int counting = 0;
            if (_isMovingLeft)
            {
                counting++;
                _pos.x -= 1;

                if (counting == _move_range.x)
                {
                    counting = 0;
                    _isMovingLeft = false;
                }
            }
            else
            {
                counting++;
                _pos.x += 1;
                if (counting == _move_range.x)
                {
                    counting = 0;
                    _isMovingLeft = true;
                }
            }
        }
    }

   
    
        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //���͸� ��������

        Player* p = player[0];


        RECT p1_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
        RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
            , _pos.y + size.y };
        RECT intersect_rect;

        if (IntersectRect(&intersect_rect, &p1_rect, &tile_rect))
        {

            float GapW = intersect_rect.right - intersect_rect.left;
            float GAPH = intersect_rect.bottom - intersect_rect.top;

            if (GapW > GAPH)
            {

                if (intersect_rect.top == tile_rect.top)
                {
                    p->_posP1.y -= GAPH;
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

            p->landing1 = true;
        }


        if (IntersectRect(&intersect_rect, &p2_rect, &tile_rect))
        {


            float GapW = intersect_rect.right - intersect_rect.left;
            float GAPH = intersect_rect.bottom - intersect_rect.top;

            if (GapW > GAPH)
            {

                if (intersect_rect.top == tile_rect.top)
                {
                    p->_posP2.y -= GAPH;
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

            p->landing2 = true;
        }

    
}


void Tile_Moving::Render(HDC mdc)
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