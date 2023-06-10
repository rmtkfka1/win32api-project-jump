#include "pch.h"
#include "Tile_KnockBack.h"
#include "ObjectManager.h"
#include "Player.h"
#include "TutorialPlayer.h"
#include "Object.h"


Tile_KnockBack::Tile_KnockBack() :Object(ObjectType::TILE)
{


}
Tile_KnockBack::~Tile_KnockBack()
{
    tile_img.Destroy();
}

void Tile_KnockBack::Init()
{
    tile_img.Load(L"리소스\\plant.png");

    size.x = 36;
    size.y = 36;


}

void Tile_KnockBack::Update()
{
    RECT tile_rect = { _pos.x + 10, _pos.y, _pos.x + size.x + 10
           , _pos.y + 10 + size.y + 10 };
    RECT intersect_rect;

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
    if (player.size() != 0) {
        Player* p = player[0];

        const vector<Tile_KnockBack*>& tiles_knockback = GET_SINGLE(ObjectManager)->GetKnockBack();   //벡터를 가져오는것


        RECT p_rectP1 = { p->_posP1.x,p->_posP1.y,p->_posP1.x + p->GetSize().x ,p->_posP1.y + p->GetSize().y };
        RECT p_rectP2 = { p->_posP2.x,p->_posP2.y,p->_posP2.x + p->GetSize().x ,p->_posP2.y + p->GetSize().y };
       

        if (IntersectRect(&intersect_rect, &p_rectP1, &tile_rect)) {

            p->_KnocBackP1 = true;
            p->_soundKnockP1 = true;

            if (p->_motionP1 == Motion::RIGHT) {
                p->_KnockPosP1.x = p->_posP1.x - 150.f;
                p->_posP1.x -= 30;
            }
            if (p->_motionP1 == Motion::LEFT) {
                p->_KnockPosP1.x = p->_posP1.x + 150.f;
                p->_posP1.x += 30;

            }


        }
        if (IntersectRect(&intersect_rect, &p_rectP2, &tile_rect)) {

            p->_KnocBackP2 = true;
            p->_soundKnockP2 = true;

            if (p->_motionP2 == Motion::RIGHT) {
                p->_KnockPosP2.x = p->_posP2.x - 150.f;
                p->_posP2.x -= 30;
            }
            if (p->_motionP2 == Motion::LEFT) {
                p->_KnockPosP2.x = p->_posP2.x + 150.f;
                p->_posP2.x += 30;
            }


        }
    }
    const vector<TutorialPlayer*>& tplayer = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
    if (tplayer.size() != 0) {
        TutorialPlayer* tp = tplayer[0];

        RECT tp_rect2 = { tp->_posP2.x,tp->_posP2.y,tp->_posP2.x + tp->GetSize().x ,tp->_posP2.y + tp->GetSize().y };
        RECT tp_rect = { tp->_posP1.x,tp->_posP1.y,tp->_posP1.x + tp->GetSize().x ,tp->_posP1.y + tp->GetSize().y };

        if (IntersectRect(&intersect_rect, &tp_rect, &tile_rect)) {
            tp->_KnocBackP1 = true;
            tp->_soundKnockP1 = true;

            if (tp->_motionP1 == Motion::RIGHT) {
                tp->_KnockPosP1.x = tp->_posP1.x - 150.f;
                tp->_posP1.x -= 30;
            }
            if (tp->_motionP1 == Motion::LEFT) {
                tp->_KnockPosP1.x = tp->_posP1.x + 150.f;
                tp->_posP1.x += 30;

            }
        }


        if (IntersectRect(&intersect_rect, &tp_rect2, &tile_rect)) {
            tp->_KnocBackP2 = true;
            tp->_soundKnockP2 = true;

            if (tp->_motionP2 == Motion::RIGHT) {
                tp->_KnockPosP2.x = tp->_posP2.x - 150.f;
                tp->_posP2.x -= 30;
            }
            if (tp->_motionP2 == Motion::LEFT) {
                tp->_KnockPosP2.x = tp->_posP2.x + 150.f;
                tp->_posP2.x += 30;
            }
        }
    }
}

void Tile_KnockBack::Render(HDC mdc)
{
    mdc2 = CreateCompatibleDC(mdc);
    hBitmap2 = CreateCompatibleBitmap(mdc, tile_img.GetWidth(), tile_img.GetHeight());
    SelectObject(mdc2, (HBITMAP)hBitmap2);

    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());

    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는
    if (player.size() != 0) {
        Player* p = player[0];

        Pos diff = p->GetDiffP1();
        Pos diff2 = p->GetDiffP2();

        if (p->_turn == ObjectType::PLAYER1)            // 초점이 1일 때
            _Renderpos = _pos - diff;                // << player1일 때
        else if (p->_turn == ObjectType::PLAYER2)        // 초점이 2
            _Renderpos = _pos - diff2;                // << player2일 때

        TransparentBlt(mdc, _Renderpos.x, _Renderpos.y, size.x, size.y,
            mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));
    }
    const vector<TutorialPlayer*>& tplayer = GET_SINGLE(ObjectManager)->GetTutorailPlayer();
    if (tplayer.size() != 0) {


        TransparentBlt(mdc, _pos.x, _pos.y, size.x, size.y,
            mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));
    }

    DeleteObject(hBitmap2);
    DeleteDC(mdc2);

}

void Tile_KnockBack::BoundingBox(HDC mdc) {
    const vector<Player*>& player = GET_SINGLE(ObjectManager)->GetPlayer();  //벡터를 가져오는

    Player* p = player[0];

    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
    oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

    RECT Box{ _pos.x, _pos.y, _pos.x + size.x, _pos.y + size.y };
    RECT RenderBox{ _Renderpos.x, _Renderpos.y, _Renderpos.x + size.x, _Renderpos.y + size.y };


    if (p->_turn == ObjectType::PLAYER1) {
        RenderBox.left = Box.left - p->_DiffP1.x + 20;
        RenderBox.top = Box.top - p->_DiffP1.y + 20;
        RenderBox.right = Box.right - p->_DiffP1.x - 20;
        RenderBox.bottom = Box.bottom - p->_DiffP1.y + 20;
    }
    else if (p->_turn == ObjectType::PLAYER2) {
        RenderBox.left = Box.left - p->_DiffP2.x + 10;
        RenderBox.top = Box.top - p->_DiffP2.y + 10;
        RenderBox.right = Box.right - p->_DiffP2.x + 10;
        RenderBox.bottom = Box.bottom - p->_DiffP2.y + 10;
    }




    FrameRect(mdc, &RenderBox, hBrush);


    SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
    DeleteObject(hBrush);
}