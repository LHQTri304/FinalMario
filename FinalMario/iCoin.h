#pragma once
#include "GameObject.h"

#pragma region Coin
#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
#pragma endregion

#pragma region HidedCoin
#define COIN_ACTIVATED_SPEED 0.001f

#define COIN_PIXEL_MOVING_Y 64

#define COIN_STATE_WAIT 100
#define COIN_STATE_ACTIVATED 200

class CHidedCoin : public CGameObject
{
protected:
	float ax;
	float ay;
	float iy;
	float pixelMovingY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CHidedCoin(float x, float y);
	virtual void SetState(int state);
};
#pragma endregion