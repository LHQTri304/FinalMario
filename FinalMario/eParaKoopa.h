#pragma once
#include "GameObject.h"

#define KOOPA_FLIGHT_TIME	33.0f
#define KOOPA_FLYING_SPEED	0.1f

#define KOOPA_STATE_FLYING 300
#define KOOPA_STATE_DROPING 301

#define ID_ANI_KOOPA_FLYING_LEFT 5007
#define ID_ANI_KOOPA_FLYING_RIGHT 5008

class CParaKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;
	float iy;
	int respawnCountdown;
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

	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);

public:
	CParaKoopa(float x, float y);
	virtual void SetState(int state);
};