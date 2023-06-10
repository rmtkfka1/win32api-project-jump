#include "pch.h"
#include "TutorialBottom.h"
#include "Tile.h"
#include "ObjectManager.h"
#include "TutorialPlayer.h"
#include "Object.h"
#include "Tile_bottom.h"


TutorialBottom::TutorialBottom() :Tile_bottom()
{


}


TutorialBottom::~TutorialBottom()
{
    tile_img.Destroy();

}

void TutorialBottom::Init()
{
    tile_img.Load(L"리소스\\grass.png");

    _pos.x = 0;
    _pos.y = 439 + 32;

    size.x = tile_img.GetWidth() * 2;
    size.y = tile_img.GetHeight() * 2.5;

}

void TutorialBottom::Update()
{
    {
        const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();  //벡터를 가져오는

        TutorialPlayer* p = player[0];

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
            p->fallP1 = false;
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
            p->fallP2 = false;
        }


    }

}

void TutorialBottom::Render(HDC mdc)
{
    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(0, 0, 0)); // GDI: 브러시 만들기
    oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기
    Rectangle(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
    DeleteObject(hBrush);

    const vector<TutorialPlayer*>& player = GET_SINGLE(ObjectManager)->GetTutorailPlayer();  //벡터를 가져오는




    hBitmap2 = CreateCompatibleBitmap(mdc, tile_img.GetWidth(), tile_img.GetHeight());
    mdc2 = CreateCompatibleDC(mdc);
    SelectObject(mdc2, (HBRUSH)hBitmap2);


    tile_img.Draw(mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight()
        , 0, 0, tile_img.GetWidth(), tile_img.GetHeight());

    TransparentBlt(mdc, _pos.x, _pos.y, size.x, size.y,
        mdc2, 0, 0, tile_img.GetWidth(), tile_img.GetHeight(), RGB(0, 0, 0));

    DeleteDC(mdc2);
    DeleteObject(hBitmap2);


}

void TutorialBottom::BoundingBox(HDC mdc) {


    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
    oldBrush = (HBRUSH)SelectObject(mdc, hBrush); // 새로운 브러시 선택하기

    RECT Box{ _pos.x, _pos.y, _pos.x + size.x, _pos.y + size.y };





    FrameRect(mdc, &Box, hBrush);


    SelectObject(mdc, oldBrush); // 이전의 브러시로 돌아가기
    DeleteObject(hBrush);
}