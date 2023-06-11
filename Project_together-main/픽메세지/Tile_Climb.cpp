#include "pch.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "Tile_Climb.h"
#include "KeyManager.h"

Tile_Climb::Tile_Climb() :Object(ObjectType::TILE)
{
    

}


Tile_Climb::~Tile_Climb()
{
    tile_img.Destroy();

}

void Tile_Climb::Init()
{
    tile_img.Load(L"리소스\\밧줄찐찐.png");

    size.x = 25;
    size.y = 700;
    start_temp = false;
}

void Tile_Climb::Update()
{
    
        const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

        Player* p = player[0];

        const vector<Tile*>& tiles = GET_SINGLE(ObjectManager)->GetTile();   //벡터를 가져오는것

        RECT p_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
        RECT tile_rect = { _pos.x+12, _pos.y, _pos.x + size.x-12
            , _pos.y + size.y };
        RECT intersect_rect;


        if (IntersectRect(&intersect_rect, &p_rect, &tile_rect))
        {

           

            if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::D))
            {
                p->Gravity1 = true;
                p->intersect_sadari1 = false;
              
            }

            if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::A))
            {
                p->Gravity1 = true;
                p->intersect_sadari1 = false;

            }

            p->landing1 = true;
            p->intersect_sadari1 = true;
       
      
    
        }

        else
        {
            p->Gravity1 = true;
            p->intersect_sadari1 = false;
  
        }



        //===============================================================================================/
        if (IntersectRect(&intersect_rect, &p2_rect, &tile_rect))
        {

            




            if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::Right))
            {
                p->Gravity2 = true;
                p->intersect_sadari2 = false;

            }

            if (GET_SINGLE(KeyManager)->GetbuttonDown(KeyType::Left))
            {
                p->Gravity2 = true;
                p->intersect_sadari2 = false;

            }

            p->landing2 = true;
            p->intersect_sadari2 = true;
        }
        else
        {
            p->Gravity2 = true;
            p->intersect_sadari2 = false;
        }




}

void Tile_Climb::Render(HDC mdc)
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

void Tile_Climb::BoundingBox(HDC mdc) {
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