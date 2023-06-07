#include "pch.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "Tile_P1.h"
#include "Tile_P2.h"


Tile::Tile() :Object(ObjectType::TILE)
{


}


Tile::~Tile()
{
    tile_img.Destroy();

}

void Tile::Init()
{
    tile_img.Load(L"���ҽ�\\Ÿ��2.png");

    size.x = 25;
    size.y = 35;

}

void Tile::Update()
{
    {
        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //���͸� ��������

        Player* p = player[0];

        const vector<Tile*>& tiles = GET_SINGLE(ObjectManager)->GetTile();   //���͸� �������°�

        RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
        RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
            , _pos.y + size.y };
        RECT intersect_rect;

       
        if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
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

      
        //===============================================================================================/
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

}

void Tile::Render(HDC mdc)
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

    TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x,size.y,
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));

    DeleteDC(mdc2);
    DeleteObject(hBitmap2);

}