#include "InteractiveItems.h"

CItemsLevelUp::CItemsLevelUp(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	this->pixelMovingX = 0;
	this->pixelMovingY = MUSHROOM_ACTIVATED_PIXEL_MOVE_Y;
	this->kind = 0;	//Mushroom first
	this->isMovingRight = true;
	SetState(ITEMS_LEVELUP_STATE_WAIT);
}

void CItemsLevelUp::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ITEMS_LEVELUP_BBOX_WIDTH / 2;
	top = y - ITEMS_LEVELUP_BBOX_HEIGHT / 2;
	right = left + ITEMS_LEVELUP_BBOX_WIDTH;
	bottom = top + ITEMS_LEVELUP_BBOX_HEIGHT;
}

int CItemsLevelUp::IsCollidable()
{
	return 1;
};

void CItemsLevelUp::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CItemsLevelUp::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CItemsLevelUp*>(e->obj)) return;

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

	if (GetState() == ITEMS_LEVELUP_STATE_ACTIVATED)
	{
		if (kind == ITEMS_LEVELUP_KIND_MUSHROOM)	//Mushroom
		{
			if (y <= iy - pixelMovingY)
				SetState(ITEMS_LEVELUP_STATE_MOVING);
			else
				y -= MUSHROOM_ACTIVATED_SPEED;
		}
		else	//Leaf
		{
			if (y <= iy - pixelMovingY)
				SetState(ITEMS_LEVELUP_STATE_MOVING);
			else
				y -= LEAF_ACTIVATED_SPEED;
		}
	}

	if (kind == ITEMS_LEVELUP_KIND_LEAF && GetState() == ITEMS_LEVELUP_STATE_MOVING)	
	{
		if (isMovingRight)	//Moving right as Leaf
		{
			if (x >= ix + pixelMovingX)
				isMovingRight = false;
			else
				x += LEAF_SPEED;
		}
		else	//Moving left as Leaf
		{
			if (x <= ix)
				isMovingRight = true;
			else
				x -= LEAF_SPEED;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CItemsLevelUp::Render()
{
	int aniId = ID_ANI_INVISIBLE;

	if (GetState() != ITEMS_LEVELUP_STATE_WAIT)
	{
		if (kind == ITEMS_LEVELUP_KIND_MUSHROOM)	//Mushroom
		{
			aniId = ID_ANI_MUSHROOM;
		}
		else	//Leaf
		{
			if (isMovingRight)
			{
				aniId = ID_ANI_LEAF_RIGHT;
			}
			else
			{
				aniId = ID_ANI_LEAF_LEFT;
			}
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CItemsLevelUp::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEMS_LEVELUP_STATE_WAIT:
		vx = 0;
		vy = 0;
		break;
	case ITEMS_LEVELUP_STATE_ACTIVATED:
		break;
	case ITEMS_LEVELUP_STATE_MOVING:
		if (kind == ITEMS_LEVELUP_KIND_MUSHROOM)	//Mushroom
		{
			ay = MUSHROOM_GRAVITY;
			vx = MUSHROOM_SPEED;
		}
		else	//Leaf
		{
			vy = LEAF_GRAVITY;
		}
	}
}