#pragma once
#include "GameObject.h"

#define GOOMBA_FLIGHT_TIME	33.0f
#define GOOMBA_FLYING_SPEED	0.1f

#define GOOMBA_STATE_FLYING 300
#define GOOMBA_STATE_DROPING 301

#define ID_ANI_GOOMBA_FLYING 5002

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float flightTime = 0;
	BOOLEAN isGetHit;
	BOOLEAN isFlying;
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
};