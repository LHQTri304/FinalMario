#include "StationaryObject.h"

CGlassBrick::CGlassBrick(float x, float y) :CGameObject(x, y)
{
	this->isActivated = false;
	this->activated_start = -1;
	//this->timesActivated = 0;
	coin = new CCoin(x, y);
	SetState(QUESTBRICK_STATE_WAIT);	//They have the same function, just different names
}

void CGlassBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	if (!isActivated)
	{
		animations->Get(ID_ANI_GLASS_BRICK)->Render(x, y);
	}
	else
	{
		coin->Render();
	}
	RenderBoundingBox();
}

void CGlassBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CGlassBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// reset activated timer if activated time has passed
	if (isActivated && GetTickCount64() - activated_start > BRICK_ACTIVATED_TIME)
	{
		activated_start = 0;
		SetState(QUESTBRICK_STATE_WAIT);
	}
	coin->Update(dt);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGlassBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTBRICK_STATE_WAIT:
		isActivated = false;
		break;
	case QUESTBRICK_STATE_ACTIVATED:
		if (!isActivated)
		{
			coin->SetState(COIN_STATE_ACTIVATED);
			isActivated = true;
			activated_start = GetTickCount64();
			//timesActivated++;
		}
		break;
	}
}