#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_FLYING_SPEED		-0.45f
#define MARIO_FALLING_SPEED		-0.1f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_ENTER_PIPE		602


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HELD_SHELL_RIGHT 1003
#define ID_ANI_MARIO_HELD_SHELL_LEFT 1004

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HELD_SHELL_RIGHT 1800
#define ID_ANI_MARIO_SMALL_HELD_SHELL_LEFT 1801

// RACCOON MARIO

#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1103
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1104

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1203
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1204

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1303
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1304

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 1403
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 1404

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 1503
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 1504

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 1603
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 1604

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 1703
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 1704

#define ID_ANI_MARIO_RACCOON_HELD_SHELL_RIGHT 1803
#define ID_ANI_MARIO_RACCOON_HELD_SHELL_LEFT 1804

#pragma endregion

//#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON		3

#define MARIO_BIG_BBOX_WIDTH  12
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  12
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  11
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_RACCOON_BBOX_WIDTH  12
#define MARIO_RACCOON_BBOX_HEIGHT 24
#define MARIO_RACCOON_SITTING_BBOX_WIDTH  12
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 16


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLYABLE_TIME 2500


#define RENDER_WIDTH 180

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float ix;				// start x (initial)
	float iy;				// start y (initial)

	int level; 
	int untouchable;
	int flyable;
	int coin;
	int numOfPipeAllow;
	int enterPipeDown;

	ULONGLONG untouchable_start;
	ULONGLONG flyable_start;

	BOOLEAN isOnPlatform;
	BOOLEAN isPressingKeyA;
	BOOLEAN isHoldingShell;
	BOOLEAN isReadyToUsePipe;

	//Enemies
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);

	void OnCollisionWithFirePlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBitePlant(LPCOLLISIONEVENT e);

	//Disappear-able
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithStar(LPCOLLISIONEVENT e);

	void OnCollisionWithBrickCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickLevelUp(LPCOLLISIONEVENT e);

	//Special blocks
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithButtonBrick(LPCOLLISIONEVENT e);

	//Others
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		ix = x; iy = y;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		flyable = 0;
		coin = 0;
		numOfPipeAllow = 0;
		enterPipeDown = 1;

		untouchable_start = -1;
		flyable_start = -1;

		isOnPlatform = false;
		isPressingKeyA = false;
		isHoldingShell = false;
		isReadyToUsePipe = false;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetState(int state);
	void SetLevel(int l);
	void SetNumOfPipeAllow(int num) { this->numOfPipeAllow = num; }
	void SetNumOfPipeMinus() { this->numOfPipeAllow--; }
	void SetEnterPipeDown(int downAllow) { this->enterPipeDown = downAllow; }
	void SetPressingKeyA(BOOLEAN isPressing) { this->isPressingKeyA = isPressing; }
	void SetHoldingShell(BOOLEAN isHolding) { this->isHoldingShell = isHolding; }

	int GetLevel() { return level; }
	int GetFlyable() { return flyable; }
	int GetEnterPipeDown() { return enterPipeDown; }
	BOOLEAN GetPressingKeyA() { return isPressingKeyA; }
	BOOLEAN GetIsOnPlatform() { return isOnPlatform; }
	BOOLEAN GetIsReadyToUsePipe() { return isReadyToUsePipe; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartFlyable() { flyable = 1; flyable_start = GetTickCount64(); }

	void LevelUp();
	void LevelDown();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};