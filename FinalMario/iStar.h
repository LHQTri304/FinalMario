#pragma once
#include "GameObject.h"

#define ID_ANI_STAR_WAIT 11005
#define ID_ANI_STAR_ACTIVATED 11006

#define STAR_GRAVITY 0.0018f	//Count as "ay" because star drop normally
#define STAR_SPEED_X 0.0005f
#define STAR_SPEED_Y 0.0025f
#define STAR_ACTIVATED_SPEED 0.5f

#define STAR_BBOX_WIDTH 16
#define STAR_BBOX_HEIGHT 16

#define STAR_PIXEL_MOVING_Y 80

#define STAR_STATE_WAIT 100
#define STAR_STATE_ACTIVATED 200
#define STAR_STATE_MOVING_DOWN 300

class CStar : public CGameObject
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
	CStar(float x, float y);
	virtual void SetState(int state);
};