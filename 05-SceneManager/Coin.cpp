#include "Coin.h"

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

//*********************//
#pragma region Mushroom
CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->iy = y;
	this->pixelMoving = MUSHROOM_ACTIVATED_PIXEL_MOVE;
	SetState(MUSHROOM_STATE_WAIT);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == MUSHROOM_STATE_ACTIVATED)
	{
		if (y <= iy - pixelMoving)
			SetState(MUSHROOM_STATE_MOVING);
		else
			y -= MUSHROOM_ACTIVATED_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	int aniId = ID_ANI_MUSHROOM;
	if (GetState() == MUSHROOM_STATE_WAIT)
	{
		aniId = ID_ANI_INVISIBLE_OBJ;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_WAIT:
		vx = 0;
		vy = 0;
		break;
	case MUSHROOM_STATE_ACTIVATED:
		break;
	case MUSHROOM_STATE_MOVING:
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_SPEED;
		break;
	}
}
#pragma endregion

//*********************//
#pragma region Leaf
CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	this->pixelMovingX = LEAF_PIXEL_MOVING_X;
	this->pixelMovingY = LEAF_PIXEL_MOVING_Y;
	SetState(LEAF_STATE_WAIT);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == LEAF_STATE_ACTIVATED)
	{
		if (y <= iy - pixelMovingY)
			SetState(LEAF_STATE_MOVING_RIGHT);
		else
			y -= LEAF_ACTIVATED_SPEED;
	}

	if (GetState() == LEAF_STATE_MOVING_RIGHT)
	{
		if (x >= ix + pixelMovingX)
			SetState(LEAF_STATE_MOVING_LEFT);
		else
			x += LEAF_SPEED;
	}

	if (GetState() == LEAF_STATE_MOVING_LEFT)
	{
		if (x <= ix)
			SetState(LEAF_STATE_MOVING_RIGHT);
		else
			x -= LEAF_SPEED;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_LEFT;
	if (GetState() == LEAF_STATE_MOVING_RIGHT)
	{
		aniId = ID_ANI_LEAF_RIGHT;
	}
	if (GetState() == LEAF_STATE_WAIT)
	{
		aniId = ID_ANI_INVISIBLE_OBJ;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_WAIT:
		vx = 0;
		vy = 0;
		break;
	case LEAF_STATE_ACTIVATED:
		break;
	case LEAF_STATE_MOVING_LEFT:
		vy = LEAF_GRAVITY;
		break;
	case LEAF_STATE_MOVING_RIGHT:
		vy = LEAF_GRAVITY;
		break;
	}
}
#pragma endregion

//*********************//
#pragma region Star
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
#pragma endregion

//*********************//
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
	int aniId = ID_ANI_COIN;
	if (GetState() == COIN_STATE_WAIT)
	{
		aniId = ID_ANI_INVISIBLE_OBJ;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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