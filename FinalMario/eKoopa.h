#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

#pragma region FakeHead

class CFakeHead : public CGameObject
{
protected:
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFakeHead(float x, float y);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#pragma endregion

//**************************//
#pragma region Koopa

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	CFakeHead* fakeHead;

	ULONGLONG stun_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithBrickLevelUp(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);


public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion