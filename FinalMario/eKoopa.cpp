#include "Enemies.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	fakeHead = new CFakeHead(x, y);
	stun_start = -1;
	SetState(KOOPA_STATE_MOVING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_STUNNED 
		|| state == KOOPA_STATE_REVIVE
		|| state == KOOPA_STATE_KICKED)
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
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
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


void CKoopa::OnCollisionWithBrickLevelUp(LPCOLLISIONEVENT e)
{
	CQuestBrickLevelUp* questBrick = dynamic_cast<CQuestBrickLevelUp*>(e->obj);

	// Hit when being kicked >> Activate the QuestBrick 
	questBrick->SetState(QUESTBRICK_STATE_ACTIVATED);
}

void CKoopa::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e)
{
	CGlassBrick* glassBrick = dynamic_cast<CGlassBrick*>(e->obj);

	// Hit when being kicked >> Break the GlassBrick
	if (GetState() == KOOPA_STATE_KICKED)
		glassBrick->Delete();
}


void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

		//fake head:..
		float fHeadX, fHeadY;
		if (GetState() == KOOPA_STATE_MOVING)
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


void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_STUNNED;
	if (vx > 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	else if (vx < 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	else if (state == KOOPA_STATE_STUNNED)
	{
		if (GetTickCount64() - stun_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_STUNNED;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	fakeHead->RenderBoundingBox();
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		stun_start = GetTickCount64();
		y -= KOOPA_BBOX_HEIGHT / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_MOVING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_REVIVE:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		ax = 0;
		ay = KOOPA_GRAVITY;
		stun_start = -1;
		SetState(KOOPA_STATE_MOVING);
		break;
	case KOOPA_STATE_KICKED:
		y -= KOOPA_BBOX_HEIGHT_STUNNED / 2;
		vx = KOOPA_KICKED_SPEED;
		break;
	}
}