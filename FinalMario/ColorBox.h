#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COLOR_BOX 12000

#define	COLOR_BOX_WIDTH 10
#define COLOR_BOX_BBOX_WIDTH 10
#define COLOR_BOX_BBOX_HEIGHT 16

class CCOLOR_BOX : public CGameObject {
public:
	CCOLOR_BOX(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};