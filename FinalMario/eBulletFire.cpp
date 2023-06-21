#include "Enemies.h"

CBulletFire::CBulletFire(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	moveTime = BULLETFIRE_MOVE_TIME;
	delayTime = BULLETFIRE_DELAY_TIME;
	isMoving = false;
	SetState(BULLETFIRE_STATE_INSIDE_PLANT);
}

void CBulletFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLETFIRE_BBOX_WIDTH / 2;
	top = y - BULLETFIRE_BBOX_HEIGHT / 2;
	right = left + BULLETFIRE_BBOX_WIDTH;
	bottom = top + BULLETFIRE_BBOX_HEIGHT;
}

void CBulletFire::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBulletFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CFirePlant*>(e->obj))
		SetState(BULLETFIRE_STATE_DELAY);
}

void CBulletFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float xMario, yMario;
	mario->GetPosition(xMario, yMario);

	if (GetState() == BULLETFIRE_STATE_DELAY)
	{
		if (delayTime <= 0)
		{
			if (xMario < x && yMario < y)
				SetState(BULLETFIRE_STATE_FIRING_UPLEFT);
			else if (xMario < x && yMario > y)
				SetState(BULLETFIRE_STATE_FIRING_DOWNLEFT);
			else if (xMario > x && yMario < y)
				SetState(BULLETFIRE_STATE_FIRING_UPRIGHT);
			else
				SetState(BULLETFIRE_STATE_FIRING_DOWNRIGHT);
			delayTime = BULLETFIRE_DELAY_TIME;
		}
		else
			delayTime--;
	}

	else if (isMoving)
	{
		if (moveTime <= 0)
		{
			SetState(BULLETFIRE_STATE_INSIDE_PLANT);
			moveTime = BULLETFIRE_MOVE_TIME;
		}
		else
			moveTime--;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBulletFire::Render()
{
	int aniId = ID_ANI_BULLETFIRE_MOVE;
	if (state == BULLETFIRE_STATE_INSIDE_PLANT || state == BULLETFIRE_STATE_DELAY)
	{
		aniId = ID_ANI_BULLETFIRE_STAY;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBulletFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLETFIRE_STATE_INSIDE_PLANT:
		x = ix;
		y = iy;	//So the bullet will begin at the center of the plant's head
		vx = 0;
		vy = 0;
		isMoving = false;
		break;
	case BULLETFIRE_STATE_FIRING_UPLEFT:
		vx = -BULLETFIRE_MOVING_SPEED_X;
		vy = -BULLETFIRE_MOVING_SPEED_Y;
		isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_DOWNLEFT:
		vx = -BULLETFIRE_MOVING_SPEED_X;
		vy = BULLETFIRE_MOVING_SPEED_Y;
		isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_UPRIGHT:
		vx = BULLETFIRE_MOVING_SPEED_X;
		vy = -BULLETFIRE_MOVING_SPEED_Y;
		isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_DOWNRIGHT:
		vx = BULLETFIRE_MOVING_SPEED_X;
		vy = BULLETFIRE_MOVING_SPEED_Y;
		isMoving = true;
		break;
	case BULLETFIRE_STATE_DELAY:
		break;
	}
}