#pragma once
#include "GameObject.h"

#include "eGoomba.h"
#include "eParaGoomba.h"

#define RESPAWN_COUNTDOWN 1000

//**************************//

//*********************//
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

//**************************//
#pragma region ParaKoopa
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
#pragma endregion

//*********************//
#pragma region FirePlant
#define FIREPLANT_MOVING_SPEED 0.05f

#define FIREPLANT_BBOX_WIDTH 16
#define FIREPLANT_BBOX_HEIGHT 24

#define FIREPLANT_LOWEST_HEIGHT 200
#define FIREPLANT_FIRE_TIME 50	//Pause time

#define FIREPLANT_STATE_MOVING_UP 100
#define FIREPLANT_STATE_MOVING_DOWN 101
#define FIREPLANT_STATE_FIRING 200

#define ID_ANI_FIREPLANT_MOVING_LEFT 5009
#define ID_ANI_FIREPLANT_MOVING_RIGHT 5109
#define ID_ANI_FIREPLANT_FIRING_UPLEFT 5010
#define ID_ANI_FIREPLANT_FIRING_DOWNLEFT 5110
#define ID_ANI_FIREPLANT_FIRING_UPRIGHT 5210
#define ID_ANI_FIREPLANT_FIRING_DOWNRIGHT 5310

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

#define BULLETFIRE_MOVING_SPEED_X 0.05f
#define BULLETFIRE_MOVING_SPEED_Y 0.02f

#define BULLETFIRE_BBOX_WIDTH 9
#define BULLETFIRE_BBOX_HEIGHT 9

#define BULLETFIRE_MOVE_TIME 200
#define BULLETFIRE_DELAY_TIME 25

#define BULLETFIRE_STATE_INSIDE_PLANT 100
#define BULLETFIRE_STATE_DELAY 101
#define BULLETFIRE_STATE_FIRING_UPLEFT 200
#define BULLETFIRE_STATE_FIRING_DOWNLEFT 201
#define BULLETFIRE_STATE_FIRING_UPRIGHT 202
#define BULLETFIRE_STATE_FIRING_DOWNRIGHT 203

#define ID_ANI_BULLETFIRE_MOVE 5011
#define ID_ANI_BULLETFIRE_STAY 5012

class CBulletFire : public CGameObject
{
protected:
	float ax;
	float ay;
	float ix;	// i = initial
	float iy;
	float moveTime;
	float delayTime;
	BOOLEAN isMoving;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable()
	{
		return (state == BULLETFIRE_STATE_INSIDE_PLANT);
	}
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBulletFire(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion

//*********************//
#pragma region BitePlant
#define BITEPLANT_MOVING_SPEED 0.05f

#define BITEPLANT_BBOX_WIDTH 16
#define BITEPLANT_BBOX_HEIGHT 24

#define BITEPLANT_LOWEST_HEIGHT 200
#define BITEPLANT_BITE_TIME 75	//Pause time

#define BITEPLANT_STATE_MOVING_UP 100
#define BITEPLANT_STATE_MOVING_DOWN 101
#define BITEPLANT_STATE_BITING 150

#define ID_ANI_BITEPLANT_BITING 5013

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
#pragma endregion