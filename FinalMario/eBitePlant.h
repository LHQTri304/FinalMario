#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

class CBitePlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float highestHeight;
	float biteTime;
	BOOLEAN isMoving;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBitePlant(float x, float y);
	virtual void SetState(int state);
};