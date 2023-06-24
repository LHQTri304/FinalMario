#include "Enemies.h"

CFirePlant::CFirePlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->highestHeight = this->y;
	this->fireTime = FIREPLANT_FIRE_TIME;
	isMoving = true;

	bullet = new CBulletFire(x, y);
	SetState(FIREPLANT_STATE_MOVING_DOWN);
}

void CFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREPLANT_BBOX_WIDTH / 2;
	top = y - FIREPLANT_BBOX_HEIGHT / 2;
	right = left + FIREPLANT_BBOX_WIDTH;
	bottom = top + FIREPLANT_BBOX_HEIGHT;
}

void CFirePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFirePlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	return;
}

void CFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetState() == FIREPLANT_STATE_MOVING_UP && y < highestHeight)
	{
		y = highestHeight;
		SetState(FIREPLANT_STATE_FIRING);
	}

	if (GetState() == FIREPLANT_STATE_MOVING_DOWN && y >= FIREPLANT_LOWEST_HEIGHT)
	{
		SetState(FIREPLANT_STATE_MOVING_UP);
	}

	if (GetState() == FIREPLANT_STATE_FIRING)
	{
		if (fireTime <= 0)
		{
			SetState(FIREPLANT_STATE_MOVING_DOWN);
			fireTime = FIREPLANT_FIRE_TIME;
		}
		else
			fireTime--;
	}

	bullet->Update(dt, coObjects);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFirePlant::Render()
{
	int aniId;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	float xMario, yMario;
	mario->GetPosition(xMario, yMario);

	if (xMario < x)
		aniId = ID_ANI_FIREPLANT_MOVING_LEFT;
	else
		aniId = ID_ANI_FIREPLANT_MOVING_RIGHT;

	if (state == FIREPLANT_STATE_FIRING)
	{
		if (xMario < x && yMario < y)
			aniId = ID_ANI_FIREPLANT_FIRING_UPLEFT;
		else if (xMario < x && yMario > y)
			aniId = ID_ANI_FIREPLANT_FIRING_DOWNLEFT;
		else if (xMario > x && yMario < y)
			aniId = ID_ANI_FIREPLANT_FIRING_UPRIGHT;
		else
			aniId = ID_ANI_FIREPLANT_FIRING_DOWNRIGHT;
	}

	bullet->Render();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CFirePlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREPLANT_STATE_MOVING_UP:
		vy = -FIREPLANT_MOVING_SPEED;
		break;
	case FIREPLANT_STATE_MOVING_DOWN:
		vy = FIREPLANT_MOVING_SPEED;
		break;
	case FIREPLANT_STATE_FIRING:
		vy = 0;
		break;
	}
}