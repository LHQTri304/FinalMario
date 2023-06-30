#include "Enemies.h"

CParaKoopa::CParaKoopa(float x, float y, int lv) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->level = lv;
	isOnPlatform = false;
	stun_start = -1;
	fakeHead = new CFakeHead(x, y);
	SetState(KOOPA_STATE_MOVING);
}

void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == KOOPA_LEVEL_SHELL)
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
	if (dynamic_cast<CMario*>(e->obj)) 
	{
		vy = -KOOPA_AVOID_FALL_BUG_VY;
		return;
	}
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

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
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

void CParaKoopa::LevelUp()
{
	if (level == KOOPA_LEVEL_SHELL)
	{
		level = KOOPA_LEVEL_WALK;
		SetState(KOOPA_STATE_MOVING);
	}
	else if (level == KOOPA_LEVEL_WALK)
	{
		level = KOOPA_LEVEL_FLY;
	}
	return;
}

void CParaKoopa::LevelDown()
{
	if (level == KOOPA_LEVEL_FLY)
	{
		level = KOOPA_LEVEL_WALK;
	}
	else if (level == KOOPA_LEVEL_WALK)
	{
		level = KOOPA_LEVEL_SHELL;
		SetState(KOOPA_STATE_STUNNED);
	}
	vy = 0.5;
	return;
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

		if (level == KOOPA_LEVEL_FLY && isOnPlatform)
		{
			vy = -KOOPA_FLYING_SPEED;
		}

		isOnPlatform = false;


		//fake head:..
		float fHeadX, fHeadY;
		if (level == KOOPA_LEVEL_WALK)
		{
			fakeHead->GetPosition(fHeadX, fHeadY);

			if (fHeadY > this->y)	//Ready to fall
			{
				vx = -vx;
			}

			if (vx > 0)
			{
				fakeHead->SetPosition(x + KOOPA_BBOX_WIDTH / 2, y - KOOPA_BBOX_HEIGHT);
			}
			else
			{
				fakeHead->SetPosition(x - KOOPA_BBOX_WIDTH / 2, y - KOOPA_BBOX_HEIGHT);
			}
		}

		fakeHead->Update(dt, coObjects);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}


void CParaKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_STUNNED;
	if (level == KOOPA_LEVEL_SHELL)
	{
		if (state == KOOPA_STATE_STUNNED && GetTickCount64() - stun_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}
	
	else if (vx > 0)
	{
		if (level == KOOPA_LEVEL_FLY)
			aniId = ID_ANI_KOOPA_FLYING_RIGHT;
		else
			aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (vx < 0)
	{
		if (level == KOOPA_LEVEL_FLY)
			aniId = ID_ANI_KOOPA_FLYING_LEFT;
		else
			aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	fakeHead->RenderBoundingBox();
	RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		stun_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_STUNNED) / 3;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_MOVING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_REVIVE:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		stun_start = -1;
		LevelUp();
		break;
	case KOOPA_STATE_KICKED:
		vx = -KOOPA_KICKED_SPEED;
		break;

	}
}