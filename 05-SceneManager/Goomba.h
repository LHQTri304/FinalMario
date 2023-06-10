#pragma once
#include "GameObject.h"

#pragma region Goomba
#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion

//**************************//
#pragma region ParaGoomba
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
#pragma endregion

//**************************//
#pragma region Koopa
#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_KICKED_SPEED 0.5f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_STUNNED 16

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

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

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
	CParaKoopa(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion

//*********************//
#pragma region FirePlant
#define FIREPLANT_MOVING_SPEED 0.05f

#define FIREPLANT_BBOX_WIDTH 16
#define FIREPLANT_BBOX_HEIGHT 24

#define FIREPLANT_MOVE_TIME 100
#define FIREPLANT_FIRE_TIME 50	//Pause time

#define FIREPLANT_STATE_MOVING_UP 100
#define FIREPLANT_STATE_MOVING_DOWN 101
#define FIREPLANT_STATE_FIRING 200
#define FIREPLANT_STATE_PAUSE 201

#define ID_ANI_FIREPLANT_MOVING 5009
#define ID_ANI_FIREPLANT_FIRING 5010

class CFirePlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float MoveTime;
	float FireTime;
	BOOLEAN isMoving;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFirePlant(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion