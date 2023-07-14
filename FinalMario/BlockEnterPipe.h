#pragma once
#include "GameObject.h"

class CBlockEnterPipe : public CGameObject
{
protected:
	int kind;	//0: Move up | 1: Move Down

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) {}

	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}

public:
	CBlockEnterPipe(float x, float y, int kind) { this->kind = kind; }
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};