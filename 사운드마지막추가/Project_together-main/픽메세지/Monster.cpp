#include "pch.h"
#include "Monster.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Object.h"
#include "TimeManager.h"


Monster::Monster() :Object(ObjectType::MONSTER)
{


}


Monster::~Monster()
{
    tile_img.Destroy();

}

void Monster::Init()
{
    tile_img.Load(L"리소스\\Bullet.png");

    size.x = 25;
    size.y = 35;

    _move_range = Pos(200, 200);
    _stat.speed = 1;
    //_first_move_renge = _move_range;
    _isMovingUp = false;
    _isMovingLeft = true;
    _DoyouWant_UP = true;
    counting = 0;
}

void Monster::Update()
{
    if (_DoyouWant_UP)
    {
        {
            if (_isMovingUp)
            {
                counting++;
                _pos.y -= _stat.speed;

                if (counting == _move_range.y)
                {
                    counting = 0;
                    _isMovingUp = false;
                }
            }

            else
            {
                counting++;
                _pos.y += _stat.speed;
                if (counting == _move_range.y)
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
            if (_isMovingLeft)
            {
                counting++;
                _pos.x -= _stat.speed;

                if (counting == _move_range.x)
                {
                    counting = 0;
                    _isMovingLeft = false;
                }
            }
            else
            {
                counting++;
                _pos.x += _stat.speed;
                if (counting == _move_range.x)
                {
                    counting = 0;
                    _isMovingLeft = true;
                }
            }
        }
    }

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];


    RECT p1_rect = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
    RECT p2_rect = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
    RECT tile_rect = { _pos.x, _pos.y, _pos.x + size.x
        , _pos.y + size.y };
    RECT intersect_rect;

    if (IntersectRect(&intersect_rect, &p1_rect, &tile_rect))
    {
        p->_KnocBackP1 = true;
        p->_soundKnockP1 = true;
        if (p->_motionP1 == Motion::UP) {
            p->_motionP1 = Motion::RIGHT;
            p->_KnockPosP1.x = p->_posP1.x - 200.f;

            p->_posP1.x -= 40.f;
            p->_posP1.y += 10.f;
        }

        else if (p->_motionP1 == Motion::DOWN) {
            p->_motionP1 = Motion::LEFT;
            p->_KnockPosP1.x = p->_posP1.x + 200.f;

            p->_posP1.x += 40.f;
            p->_posP1.y += 10.f;
        }
        
    }

    if (IntersectRect(&intersect_rect, &p2_rect, &tile_rect))
    {
        p->_KnocBackP2 = true;
        p->_soundKnockP2 = true;
        if (p->_motionP2 == Motion::UP) {
            p->_motionP2 = Motion::RIGHT;
            p->_KnockPosP2.x = p->_posP2.x - 150.f;

            p->_posP2.x -= 40.f;
            p->_posP2.y += 10.f;
        }

        else if (p->_motionP2 == Motion::DOWN) {
            p->_motionP2 = Motion::LEFT;
            p->_KnockPosP2.x = p->_posP2.x + 150.f;

            p->_posP2.x += 40.f;
            p->_posP2.y += 10.f;
        }


    }
}

void Monster::Render(HDC mdc)
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

void Monster::BoundingBox(HDC mdc) {
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