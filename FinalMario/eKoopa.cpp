#include "Enemies.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->ix = x;
	this->iy = y;

	fakeHead = new CFakeHead(x, y);

	respawnCountdown = 0;
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
	if (state != KOOPA_STATE_KICKED && dynamic_cast<CKoopaSupportBlock*>(e->obj))
	{
		vx = -vx;
		return;
	}

	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		goomba->SetState(GOOMBA_STATE_DIE);
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}


	if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CQuestBrick*>(e->obj))
		OnCollisionWithQuestBrick(e);
	else if (dynamic_cast<CGlassBrick*>(e->obj))
		OnCollisionWithGlassBrick(e);
}

void CKoopa::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	// Hit when being kicked >> Activate Mushroom 
	if (mushroom->GetState() == MUSHROOM_STATE_WAIT && GetState() == KOOPA_STATE_KICKED
		&& mario->GetLevel() == MARIO_LEVEL_SMALL)
		mushroom->SetState(MUSHROOM_STATE_ACTIVATED);
}

void CKoopa::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	// Hit when being kicked >> Activate Leaf 
	if (leaf->GetState() == LEAF_STATE_WAIT && GetState() == KOOPA_STATE_KICKED
		&& mario->GetLevel() != MARIO_LEVEL_SMALL)
		leaf->SetState(LEAF_STATE_ACTIVATED);
}

void CKoopa::OnCollisionWithQuestBrick(LPCOLLISIONEVENT e)
{
	CQuestBrick* questBrick = dynamic_cast<CQuestBrick*>(e->obj);

	// Hit when being kicked >> Activate the QuestBrick 
	questBrick->SetState(QUESTBRICK_STATE_ACTIVATED);
}

void CKoopa::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e)
{
	CGlassBrick* glassBrick = dynamic_cast<CGlassBrick*>(e->obj);

	// Hit when being kicked >> Break the GlassBrick
	glassBrick->Delete();
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

	if (respawnCountdown <= 0)
	{
		x = ix;
		y = iy;
		SetState(KOOPA_STATE_WALKING);
		respawnCountdown = 0;
	}
	else
		respawnCountdown--;


	//fake head:..
	float fHeadX, fHeadY;
	if (GetState() == KOOPA_STATE_WALKING)
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


void CKoopa::Render()
{
	int aniId;
	if (vx > 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	else if (vx < 0 && state != KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	else if (state == KOOPA_STATE_STUNNED)
	{
		if (GetTickCount64() - die_start > KOOPA_STUNNED_TIMEOUT - KOOPA_REVIVING_TIMEOUT)
			aniId = ID_ANI_KOOPA_REVIVE;
		else
			aniId = ID_ANI_KOOPA_STUNNED;
	}
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_STUNNED;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//fakeHead->RenderBoundingBox();
	//RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_STUNNED:
		die_start = GetTickCount64();
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_STUNNED) / 2;
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
		vx = KOOPA_KICKED_SPEED;
		break;
	}
}