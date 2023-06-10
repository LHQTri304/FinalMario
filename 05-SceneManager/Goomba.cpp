#include "Goomba.h"

#pragma region Goomba
CGoomba::CGoomba(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}
#pragma endregion

//*********************//
#pragma region ParaGoomba
CParaGoomba::CParaGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
	SetState(GOOMBA_STATE_FLYING);
	isGetHit = false;
	isFlying = false;
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;

	if (e->ny != 0)	
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	//add...
	if (isFlying && !isGetHit)
	{
		SetState(GOOMBA_STATE_FLYING);
		flightTime--;
	}
	if (!isFlying && !isGetHit)
	{
		SetState(GOOMBA_STATE_DROPING);
		flightTime++;
	}

	if (flightTime <= 0)
		isFlying = false;
	if (flightTime >= GOOMBA_FLIGHT_TIME)
		isFlying = true;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_FLYING;
	if (state == GOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		isGetHit = true;
		break;

	case GOOMBA_STATE_FLYING:
		vy = -GOOMBA_FLYING_SPEED;
		break;

	case GOOMBA_STATE_DROPING:
		if (vy < 0) vy += GOOMBA_FLYING_SPEED / 2;
		break;

	}
}
#pragma endregion

//*********************//
#pragma region Koopa
CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_STUNNED)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_STUNNED / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_STUNNED;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_STUNNED) && (GetTickCount64() - die_start > KOOPA_STUNNED_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVE);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId;
	if (vx > 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	else if (vx < 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	else if (state == KOOPA_STATE_STUNNED)
	{
		if(GetTickCount64() - die_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_STUNNED;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_STUNNED) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_REVIVE:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		ax = 0;
		ay = KOOPA_GRAVITY;
		die_start = -1;
		SetState(KOOPA_STATE_WALKING);
		break;
	case KOOPA_STATE_KICKED:
		vx = -KOOPA_KICKED_SPEED;
		break;
	}
}
#pragma endregion

//*********************//
#pragma region ParaKoopa
CParaKoopa::CParaKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING);
	SetState(KOOPA_STATE_FLYING);
	isGetHit = false;
	isFlying = false;
}

void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_STUNNED)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_STUNNED / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_STUNNED;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CParaKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_STUNNED) && (GetTickCount64() - die_start > KOOPA_STUNNED_TIMEOUT))
	{
		SetState(KOOPA_STATE_REVIVE);
		return;
	}

	//add...
	if (isFlying && !isGetHit)
	{
		SetState(KOOPA_STATE_FLYING);
		flightTime--;
	}
	if (!isFlying && !isGetHit)
	{
		SetState(KOOPA_STATE_DROPING);
		flightTime++;
	}

	if (flightTime <= 0)
		isFlying = false;
	if (flightTime >= KOOPA_FLIGHT_TIME)
		isFlying = true;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaKoopa::Render()
{
	int aniId; 
	if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_STUNNED;
	
	else if (state == KOOPA_STATE_STUNNED)
	{
		if (GetTickCount64() - die_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}

	else if (vx > 0 && state)
	{
		if (isGetHit == false)
			aniId = ID_ANI_KOOPA_FLYING_RIGHT;
		else
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (vx < 0 && state)
	{
		if (isGetHit == false)
			aniId = ID_ANI_KOOPA_FLYING_LEFT;
		else
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_STUNNED) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		isGetHit = true;
		break;
	case KOOPA_STATE_REVIVE:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		ax = 0;
		die_start = -1;
		SetState(KOOPA_STATE_WALKING);
		break;
	case KOOPA_STATE_KICKED:
		vx = -KOOPA_KICKED_SPEED;
		break;

	case KOOPA_STATE_FLYING:
		vy = -KOOPA_FLYING_SPEED;
		break;

	case KOOPA_STATE_DROPING:
		if (vy < 0) vy += KOOPA_FLYING_SPEED / 2;
		break;

	}
}
#pragma endregion

//*********************//
#pragma region FirePlant
CFirePlant::CFirePlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->highestHeight = this->y;
	this->fireTime = FIREPLANT_FIRE_TIME;
	isMoving = true;
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

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFirePlant::Render()
{
	int aniId = ID_ANI_FIREPLANT_MOVING;
	if (state == FIREPLANT_STATE_FIRING)
	{
		aniId = ID_ANI_FIREPLANT_FIRING;
	}

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
#pragma endregion

//*********************//
#pragma region BulletFire
CBulletFire::CBulletFire(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->ix = x;
	this->iy = y;
	moveTime = BULLETFIRE_MOVE_TIME;
	delayTime = BULLETFIRE_DELAY_TIME;
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

	if (GetState() == BULLETFIRE_STATE_DELAY)
	{
		if (delayTime <= 0)
		{
			SetState(BULLETFIRE_STATE_FIRING);
			delayTime = BULLETFIRE_DELAY_TIME;
		}
		else
			delayTime--;
	}
	
	else if (GetState() == BULLETFIRE_STATE_FIRING)
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
	int aniId = ID_ANI_BULLETFIRE_STAY;
	if (state == BULLETFIRE_STATE_FIRING)
	{
		aniId = ID_ANI_BULLETFIRE_MOVE;
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
		break;
	case BULLETFIRE_STATE_FIRING:
		vx = -BULLETFIRE_MOVING_SPEED;
		vy = BULLETFIRE_MOVING_SPEED;
		break;
	case BULLETFIRE_STATE_DELAY:
		break;
	}
}
#pragma endregion

//*********************//
#pragma region BitePlant
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
#pragma endregion