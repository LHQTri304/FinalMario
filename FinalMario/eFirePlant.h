#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

class CBulletFire : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;	// i = initial
	float iy;
	BOOLEAN isCollidingProperly;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBulletFire(float x, float y);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

class CFirePlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float highestHeight;
	float fireTime;
	BOOLEAN isMoving;

	int faceFire;	// 0 = UpLeft | 1 = DownLeft | 2 = UpRight | 3 = DownRight
	int faceMove;	// 0 = Left | 1 = Right

	CBulletFire* bullet;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFirePlant(float x, float y);
	virtual void SetState(int state);
};
