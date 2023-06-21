#pragma once

#include "GameObject.h"

#include "BackgroundStuff.h"

#define ID_ANI_INVISIBLE_BLOCK 10000
#define ID_ANI_DIRT_BRICK 10001
#define ID_ANI_GLASS_BRICK 10002
#define ID_ANI_QUEST_BRICK 10003
#define ID_ANI_BLANK_BRICK 10004

#define ID_ANI_TREES 10005
#define ID_ANI_BUSH 10006
#define ID_ANI_CLOUD1 10007
#define ID_ANI_CLOUD2 10008
#define ID_ANI_CLOUD3 10009
#define ID_ANI_BLACK_END 10010
#define ID_ANI_BORDER_END 10011

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CDirtBrick : public CGameObject {
public:
	CDirtBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CGlassBrick : public CGameObject {
public:
	CGlassBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};



//*********************//

#define QUESTBRICK_STATE_WAIT 100
#define QUESTBRICK_STATE_ACTIVATED 200

class CQuestBrick : public CGameObject {
public:
	CQuestBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};