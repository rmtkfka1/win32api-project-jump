#pragma once
#include "Scene.h"
class Lobby : public Scene
{
public:

	DECLARE_SINGLE(Lobby);
	virtual ~Lobby();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	void BoundingBox(HDC mdc);

public:



	CImage Lobby_img;


	FMOD::System* ssystem;
	FMOD::Sound* sound1;	// p1 ����
	FMOD::Channel* channel;
	FMOD_RESULT result;
	void* extradriverdata = 0;

};

