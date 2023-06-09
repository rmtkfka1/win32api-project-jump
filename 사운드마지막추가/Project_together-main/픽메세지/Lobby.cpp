#include "pch.h"
#include "Lobby.h"
#include "KeyManager.h"
#include "SceanManager.h"

Lobby::~Lobby()
{
	Lobby_img.Destroy();
	ssystem->release();
}

void Lobby::Init()
{
	Lobby_img.Load(L"리소스\\로비.png");


	result = FMOD::System_Create(&ssystem);

	ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ssystem->createSound("Sound\\Lobby.wav",
		FMOD_LOOP_NORMAL, 0, &sound1);
	ssystem->playSound(sound1, 0, false, &channel);

}

void Lobby::Update()
{
	POINT MOUSEPOSE = GET_SINGLE(KeyManager)->GetMousePos();



	if (GET_SINGLE(KeyManager)->Getbutton(KeyType::LeftMouse))
	{
		if (MOUSEPOSE.x > 706 && MOUSEPOSE.x < 1109 && MOUSEPOSE.y>53 && MOUSEPOSE.y < 183)
		{
			GET_SINGLE(SceneManager)->ChangeScene(SceneType::STAGE1);
		}


		if (MOUSEPOSE.x > 705 && MOUSEPOSE.x < 1103 && MOUSEPOSE.y>335 && MOUSEPOSE.y < 459)
		{
			exit(0);
		}
	}

}

void Lobby::Render(HDC mdc)
{

	POINT MOUSEPOSE = GET_SINGLE(KeyManager)->GetMousePos();


	Lobby_img.Draw(mdc, 0, 0, Lobby_img.GetWidth(), Lobby_img.GetHeight()
		, 0, 0, Lobby_img.GetWidth(), Lobby_img.GetHeight());

	wstring str = std::format(L"Mouse({0},{1})", MOUSEPOSE.x, MOUSEPOSE.y);
	TextOut(mdc, 0, 0, str.c_str(), static_cast<int32>(str.size()));

}

void Lobby::BoundingBox(HDC mdc)
{
}
