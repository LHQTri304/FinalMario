#pragma once

#include "InteractiveItems.h"


//*********************//
#pragma region Mushroom (& Leaf)
#define ID_ANI_MUSHROOM 11001

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.07f
#define MUSHROOM_ACTIVATED_SPEED 0.2f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_ACTIVATED_PIXEL_MOVE 16

#define MUSHROOM_STATE_WAIT 100
#define MUSHROOM_STATE_ACTIVATED 200
#define MUSHROOM_STATE_MOVING 300

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float iy;	//initial
	float pixelMoving;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state == MUSHROOM_STATE_MOVING; };	//Don't let anything change the mushroom if it's not activated yet.
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion

//*********************//
#pragma region Leaf
#define ID_ANI_LEAF_LEFT 11002
#define ID_ANI_LEAF_RIGHT 11003
#define ID_ANI_INVISIBLE_OBJ 11004

#define LEAF_GRAVITY 0.02f	//Count as vy instead of ay because leaf drop slowy
#define LEAF_SPEED 1.25f
#define LEAF_ACTIVATED_SPEED 3.5f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16

#define LEAF_PIXEL_MOVING_X 32
#define LEAF_PIXEL_MOVING_Y 48

#define LEAF_STATE_WAIT 100
#define LEAF_STATE_ACTIVATED 200
#define LEAF_STATE_MOVING_LEFT 300
#define LEAF_STATE_MOVING_RIGHT 301

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;	//initial
	float iy;
	float pixelMovingX;
	float pixelMovingY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion

//*********************//

//*********************//