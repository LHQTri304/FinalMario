#include "Enemies.h"

CParaKoopa::CParaKoopa(float x, float y, int lv) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->level = lv;
	isOnPlatform = false;
	stun_start = -1;
	fakeHead = new CFakeHead(x, y);
	if (level == KOOPA_LEVEL_FLY)
	{
		SetState(KOOPA_STATE_FLYING);
	}
	else
	{
		SetState(KOOPA_STATE_WALKING);
	}
	//isGetHit = false;
	//isFlying = false;
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
	if (dynamic_cast<CParaKoopa*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
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

	if (dynamic_cast<CQuestBrickLevelUp*>(e->obj))
		OnCollisionWithBrickLevelUp(e);
	else if (dynamic_cast<CGlassBrick*>(e->obj))
		OnCollisionWithGlassBrick(e);
}


void CParaKoopa::OnCollisionWithBrickLevelUp(LPCOLLISIONEVENT e)
{
	CQuestBrickLevelUp* questBrick = dynamic_cast<CQuestBrickLevelUp*>(e->obj);

	// Hit when being kicked >> Activate the QuestBrick 
	if (GetState() == KOOPA_STATE_KICKED)
		questBrick->SetState(QUESTBRICK_STATE_ACTIVATED);
}

void CParaKoopa::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e)
{
	CGlassBrick* glassBrick = dynamic_cast<CGlassBrick*>(e->obj);

	// Hit when being kicked >> Break the GlassBrick
	if (GetState() == KOOPA_STATE_KICKED)
		glassBrick->Delete();
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isAllowToUpdate)
	{
		vy += ay * dt;
		vx += ax * dt;

		if ((state == KOOPA_STATE_STUNNED) && (GetTickCount64() - stun_start > KOOPA_STUNNED_TIMEOUT))
		{
			SetState(KOOPA_STATE_REVIVE);
			return;
		}

		/*add...
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
		*/

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}


void CParaKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_STUNNED;
	if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_STUNNED;

	else if (state == KOOPA_STATE_STUNNED)
	{
		if (GetTickCount64() - stun_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}
	/*
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
	}*/else
		aniId = ID_ANI_KOOPA_FLYING_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		stun_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_STUNNED) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		//isGetHit = true;
		break;
	case KOOPA_STATE_REVIVE:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		ax = 0;
		stun_start = -1;
		SetState(KOOPA_STATE_WALKING);
		break;
	case KOOPA_STATE_KICKED:
		vx = -KOOPA_KICKED_SPEED;
		break;
	case KOOPA_STATE_FLYING:
		vx = -KOOPA_WALKING_SPEED;
		vy = -KOOPA_FLYING_SPEED * 5;
		break;

	}
}