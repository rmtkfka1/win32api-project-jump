#pragma once
#include "Scene.h"

class End :public Scene
{

public:
	DECLARE_SINGLE(End);
	virtual ~End();


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	void BoundingBox(HDC mdc);

public:


	CImage ending_img;


};

