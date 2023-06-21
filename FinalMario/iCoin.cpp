#include "InteractiveItems.h"

#pragma region Coin
void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
#pragma endregion

#pragma region HidedCoin
CHidedCoin::CHidedCoin(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->iy = y;
	this->pixelMovingY = COIN_PIXEL_MOVING_Y;
	SetState(COIN_STATE_WAIT);
}

void CHidedCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - COIN_BBOX_WIDTH / 2;
	top = y - COIN_BBOX_HEIGHT / 2;
	right = left + COIN_BBOX_WIDTH;
	bottom = top + COIN_BBOX_HEIGHT;
}

void CHidedCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CHidedCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CHidedCoin*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CHidedCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == COIN_STATE_ACTIVATED)
	{
		if (y <= iy - pixelMovingY)
			this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CHidedCoin::Render()
{
	if (GetState() != COIN_STATE_WAIT)
	{
		CAnimations::GetInstance()->Get(ID_ANI_COIN)->Render(x, y);
	}
	
	RenderBoundingBox();
}

void CHidedCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_WAIT:
		vx = 0;
		vy = 0;
		break;
	case COIN_STATE_ACTIVATED:
		ay = -COIN_ACTIVATED_SPEED;
		break;
	}
}
#pragma endregion