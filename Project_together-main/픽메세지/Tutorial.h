#pragma once
#include "Scene.h"

class Tutorial : public Scene
{
public:

	DECLARE_SINGLE(Tutorial);
	virtual ~Tutorial();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;


	void ExPlain1(HDC);
	void ExPlain2(HDC);
	void ExPlain3(HDC);

	void BallCollision();

public:
	int		sequence{0};
	
	RECT	pinkBall{ WINDOW_WIDTH - 50, WINDOW_HEIGHT - 200, WINDOW_WIDTH - 25, WINDOW_HEIGHT - 175};
	RECT	BlueBall{ 10, WINDOW_HEIGHT - 200, 35, WINDOW_HEIGHT - 175};

	

	bool	_ballCollision[5][2]{};
	bool	_start[5]{};
	bool	_end[5]{};
	int		_cnt{ 0 };


	FMOD::System* ssystem;
	FMOD::Sound* sound1;	// p1 มกวม
	FMOD::Channel* channel;
	FMOD_RESULT result;
	void* extradriverdata = 0;
};

