#pragma once
#include "GameObject.h"

#pragma region FakeHead
#define FAKEHEAD_GRAVITY 0.2f

#define FAKEHEAD_BBOX_WIDTH 16
#define FAKEHEAD_BBOX_HEIGHT 24

#define ID_ANI_FAKEHEAD ID_ANI_BULLETFIRE_STAY

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
#define KOOPA_GRAVITY 0.0008f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_KICKED_SPEED 0.25f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_STUNNED 14

#define KOOPA_STUNNED_TIMEOUT 1500
#define KOOPA_REVIVING_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_STUNNED 200
#define KOOPA_STATE_REVIVE 201
#define KOOPA_STATE_KICKED 203

#define ID_ANI_KOOPA_WALKING_LEFT 5003
#define ID_ANI_KOOPA_WALKING_RIGHT 5004
#define ID_ANI_KOOPA_STUNNED 5005
#define ID_ANI_KOOPA_REVIVE 5006

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;
	float iy;
	int respawnCountdown;

	CFakeHead* fakeHead;

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
	CKoopa(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion