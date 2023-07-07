#include "Enemies.h"

CBulletFire::CBulletFire(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	this->wrongCollisionCountDown = BULLETFIRE_WRONG_COLLISION_TIMEOUT;
	SetState(BULLETFIRE_STATE_INSIDE_PLANT);
}

void CBulletFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLETFIRE_BBOX_WIDTH / 2;
	top = y - BULLETFIRE_BBOX_HEIGHT / 2;
	right = left + BULLETFIRE_BBOX_WIDTH;
	bottom = top + BULLETFIRE_BBOX_HEIGHT;
}

int CBulletFire::IsCollidable()
{
	return (GetState() != BULLETFIRE_STATE_INSIDE_PLANT && wrongCollisionCountDown < 0);
}

void CBulletFire::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBulletFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if ((e->nx != 0 || e->ny != 0) && e->obj->IsBlocking())
	{
		if (dynamic_cast<CMario*>(e->obj))
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			int mLevel = mario->GetLevel();

			// touch >> Level down
			if (GetState() != BULLETFIRE_STATE_INSIDE_PLANT)
			{
				mario->LevelDown();
			}
		}
		else
		{
			wrongCollisionCountDown = BULLETFIRE_WRONG_COLLISION_TIMEOUT;
		}
	}
}

void CBulletFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBulletFire::Render()
{
	if (state != BULLETFIRE_STATE_INSIDE_PLANT)
	{
		CAnimations::GetInstance()->Get(ID_ANI_BULLETFIRE_MOVE)->Render(x, y);
	}

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
		//isMoving = false;
		break;
	case BULLETFIRE_STATE_FIRING_UPLEFT:
		x = ix;
		y = iy;
		vx = -BULLETFIRE_MOVING_SPEED_X;
		vy = -BULLETFIRE_MOVING_SPEED_Y;
		//isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_DOWNLEFT:
		x = ix;
		y = iy;
		vx = -BULLETFIRE_MOVING_SPEED_X;
		vy = BULLETFIRE_MOVING_SPEED_Y;
		//isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_UPRIGHT:
		x = ix;
		y = iy;
		vx = BULLETFIRE_MOVING_SPEED_X;
		vy = -BULLETFIRE_MOVING_SPEED_Y;
		//isMoving = true;
		break;
	case BULLETFIRE_STATE_FIRING_DOWNRIGHT:
		x = ix;
		y = iy;
		vx = BULLETFIRE_MOVING_SPEED_X;
		vy = BULLETFIRE_MOVING_SPEED_Y;
		//isMoving = true;
		break;
	}
}