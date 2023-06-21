#include "Enemies.h"

CBitePlant::CBitePlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->highestHeight = this->y;
	this->biteTime = BITEPLANT_BITE_TIME;
	isMoving = true;
	SetState(BITEPLANT_STATE_MOVING_DOWN);
}

void CBitePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BITEPLANT_BBOX_WIDTH / 2;
	top = y - BITEPLANT_BBOX_HEIGHT / 2;
	right = left + BITEPLANT_BBOX_WIDTH;
	bottom = top + BITEPLANT_BBOX_HEIGHT;
}

void CBitePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBitePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	return;
}

void CBitePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == BITEPLANT_STATE_MOVING_UP && y < highestHeight)
	{
		y = highestHeight;
		SetState(BITEPLANT_STATE_BITING);
	}

	if (GetState() == BITEPLANT_STATE_MOVING_DOWN && y >= BITEPLANT_LOWEST_HEIGHT)
	{
		SetState(BITEPLANT_STATE_MOVING_UP);
	}

	if (GetState() == BITEPLANT_STATE_BITING)
	{
		if (biteTime <= 0)
		{
			SetState(BITEPLANT_STATE_MOVING_DOWN);
			biteTime = BITEPLANT_STATE_BITING;
		}
		else
			biteTime--;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBitePlant::Render()
{
	int aniId = ID_ANI_BITEPLANT_BITING;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBitePlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BITEPLANT_STATE_MOVING_UP:
		vy = -BITEPLANT_MOVING_SPEED;
		break;
	case BITEPLANT_STATE_MOVING_DOWN:
		vy = BITEPLANT_MOVING_SPEED;
		break;
	case BITEPLANT_STATE_BITING:
		vy = 0;
		break;
	}
}