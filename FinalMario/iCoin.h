#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

#pragma region Coin

class CCoin : public CGameObject {
protected:
	virtual int IsCollidable() { return (GetState() == COIN_STATE_ACTIVATED); };
	virtual int IsBlocking() { return 0; };
public:
	CCoin(float x, float y) : CGameObject(x, y) { SetState(COIN_STATE_ACTIVATED); }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};
#pragma endregion

#pragma region HidedCoin

class CHidedCoin : public CGameObject
{
protected:
	float ax;
	float ay;
	float iy;
	float pixelMovingY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CHidedCoin(float x, float y);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
#pragma endregion