#pragma once
#include "GameObject.h"

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
