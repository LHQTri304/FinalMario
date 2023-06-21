#pragma once
#include "GameObject.h"

#include "AllDefineTest.h"

#pragma region Mushroom (& Leaf)

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