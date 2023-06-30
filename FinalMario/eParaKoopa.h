#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

class CParaKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	int level;

	BOOLEAN isOnPlatform;
	ULONGLONG stun_start;
	CFakeHead* fakeHead;

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
	CParaKoopa(float x, float y, int level);
	virtual void SetState(int state);

	int GetLevel() { return level; }
	void AvoidFallBug() { vy = -KOOPA_AVOID_FALL_BUG_VY; }
	void LevelUp();
	void LevelDown();
};