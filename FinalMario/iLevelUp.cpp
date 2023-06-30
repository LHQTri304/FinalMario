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
	this->isCollidingProperly = true;
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
	if (isCollidingProperly)
	{
		return (GetState() != ITEMS_LEVELUP_STATE_DELETED);
	}
	return 0;
}

void CItemsLevelUp::OnNoCollision(DWORD dt)
{
	isCollidingProperly = true;

	x += vx * dt;
	y += vy * dt;
}

void CItemsLevelUp::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (kind == ITEMS_LEVELUP_KIND_MUSHROOM)	//Mushroom
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CGoomba*>(e->obj)) return;
		if (dynamic_cast<CFirePlant*>(e->obj)) return;
		if (dynamic_cast<CBulletFire*>(e->obj)) return;
		if (dynamic_cast<CBitePlant*>(e->obj)) return;

		if (dynamic_cast<CMario*>(e->obj))
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			int mLevel = mario->GetLevel();

			// touch >> Level up
			if (GetState() == ITEMS_LEVELUP_STATE_MOVING)
			{
				if (mLevel == MARIO_LEVEL_SMALL)
				{
					mario->SetLevel(MARIO_LEVEL_BIG);	//Small (1) >> Big (2) >> Raccoon (3)
					mario->SetSpeed(0, -MARIO_JUMP_DEFLECT_SPEED);
				}
				SetState(ITEMS_LEVELUP_STATE_DELETED);
			}
			return;
		}

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}
	else	//Leaf >> Only collides with mario
	{
		if (!dynamic_cast<CMario*>(e->obj))
		{
			isCollidingProperly = false;
			return;
		}
		else
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			int mLevel = mario->GetLevel();

			// touch >> Level up
			if (GetState() == ITEMS_LEVELUP_STATE_MOVING)
			{
				if (mLevel == MARIO_LEVEL_BIG)
				{
					mario->SetLevel(MARIO_LEVEL_RACCOON);	//Small (1) >> Big (2) >> Raccoon (3)
					mario->SetSpeed(0, -MARIO_JUMP_DEFLECT_SPEED);
				}
				SetState(ITEMS_LEVELUP_STATE_DELETED);
			}
			return;
		}
	}


}

void CItemsLevelUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == ITEMS_LEVELUP_STATE_WAIT)	//Change kind based on mario >> If activated then won't change
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			this->pixelMovingX = 0;
			this->pixelMovingY = MUSHROOM_ACTIVATED_PIXEL_MOVE_Y;
			this->kind = 0;	//Mushroom
		}
		else
		{
			this->pixelMovingX = LEAF_ACTIVATED_PIXEL_MOVE_X;
			this->pixelMovingY = LEAF_ACTIVATED_PIXEL_MOVE_Y;
			this->kind = 1;	//Leaf
		}
	}

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
			{
				isMovingRight = false;
				vx = -vx;
			}
		}
		else	//Moving left as Leaf
		{
			if (x <= ix)
			{
				isMovingRight = true;
				vx = -vx;
			}
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
	if (GetState() == ITEMS_LEVELUP_STATE_DELETED)
	{
		aniId = ID_ANI_INVISIBLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
			vx = LEAF_SPEED;
			vy = LEAF_GRAVITY;
		}
	case ITEMS_LEVELUP_STATE_DELETED:
		break;
	}
}