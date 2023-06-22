#include "InteractiveItems.h"

#pragma region Mushroom
CItemsLevelUp::CItemsLevelUp(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	//this->pixelMovingY = MUSHROOM_ACTIVATED_PIXEL_MOVE_Y;
	//this->pixelMovingX = LEAF_ACTIVATED_PIXEL_MOVE_X;
	//this->pixelMovingY = LEAF_ACTIVATED_PIXEL_MOVE_Y;
	SetState(ITEMS_LEVELUP_STATE_WAIT);
}

void CItemsLevelUp::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ITEMS_LEVELUP_BBOX_WIDTH / 2;
	top = y - ITEMS_LEVELUP_BBOX_HEIGHT / 2;
	right = left + ITEMS_LEVELUP_BBOX_WIDTH;
	bottom = top + ITEMS_LEVELUP_BBOX_HEIGHT;
}

void CItemsLevelUp::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CItemsLevelUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CItemsLevelUp*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CItemsLevelUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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


void CItemsLevelUp::Render()
{
	if (GetState() != MUSHROOM_STATE_WAIT)
	{
		CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM)->Render(x, y);
	}

	RenderBoundingBox();
}

void CItemsLevelUp::SetState(int state)
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
	if (GetState() != LEAF_STATE_WAIT)
	{
		if (GetState() == LEAF_STATE_MOVING_RIGHT)
		{
			CAnimations::GetInstance()->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
		}
		else
		{
			CAnimations::GetInstance()->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
		}
	}

	RenderBoundingBox();
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