#pragma once
#include "GameObject.h"

#include "eGoomba.h"
#include "eParaGoomba.h"
#include "eKoopa.h"
#include "eParaKoopa.h"
#include "eFirePlant.h"

#define RESPAWN_COUNTDOWN 1000

//**************************//

//*********************//

//**************************//

//*********************//
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