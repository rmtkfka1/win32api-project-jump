#pragma once
#include "Tile_bottom.h"

class TutorialBottom : Tile_bottom
{
public:

	TutorialBottom();
	virtual ~TutorialBottom() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;
};

