#include "InteractiveItems.h"

CStar::CStar(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->iy = y;
	this->pixelMovingY = STAR_PIXEL_MOVING_Y;
	SetState(STAR_STATE_WAIT);
}

void CStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - STAR_BBOX_WIDTH / 2;
	top = y - STAR_BBOX_HEIGHT / 2;
	right = left + STAR_BBOX_WIDTH;
	bottom = top + STAR_BBOX_HEIGHT;
}

void CStar::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CStar::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CStar*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == STAR_STATE_ACTIVATED)
	{
		if (y <= iy - pixelMovingY)
			SetState(STAR_STATE_MOVING_DOWN);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CStar::Render()
{
	int aniId = ID_ANI_STAR_ACTIVATED;
	if (GetState() == STAR_STATE_WAIT)
	{
		aniId = ID_ANI_STAR_WAIT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CStar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STAR_STATE_WAIT:
		vx = 0;
		vy = 0;
		break;
	case STAR_STATE_ACTIVATED:
		ax = STAR_SPEED_X;
		ay = -STAR_SPEED_Y;
		break;
	case STAR_STATE_MOVING_DOWN:
		ay = STAR_GRAVITY;
		vy = 0;
		break;
	}
}