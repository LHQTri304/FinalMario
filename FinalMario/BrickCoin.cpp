#include "StationaryObject.h"

CQuestBrickCoin::CQuestBrickCoin(float x, float y) :CGameObject(x, y)
{
	hidedCoin = new CHidedCoin(x, y-50);
	SetState(QUESTBRICK_STATE_WAIT);
}


void CQuestBrickCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
	animations->Get(ID_ANI_QUEST_BRICK)->Render(x, y);

	if (GetState() == QUESTBRICK_STATE_ACTIVATED)
		animations->Get(ID_ANI_BLANK_BRICK)->Render(x, y);

	hidedCoin->Render();

	//RenderBoundingBox();
}

void CQuestBrickCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CQuestBrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (countDownTest <= 0)
	{
		SetState(QUESTBRICK_STATE_ACTIVATED);
		hidedCoin->SetState(COIN_STATE_ACTIVATED);
	}
	else
	{
		countDownTest--;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CQuestBrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTBRICK_STATE_WAIT:
		break;
	case QUESTBRICK_STATE_ACTIVATED:
		break;
	}
}