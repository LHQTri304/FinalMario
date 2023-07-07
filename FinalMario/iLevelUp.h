#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

// Mushroom & Leaf
class CItemsLevelUp : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;	//initial
	float iy;
	float pixelMovingX;
	float pixelMovingY;

	int kind;	// 0: Mushroom | 1: Leaf
	int wrongCollisionCountDown;
	BOOLEAN	isMovingRight;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable();	//Don't let anything change the mushroom if it's not activated yet.
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CItemsLevelUp(float x, float y);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int GetKind() { return kind; }
};