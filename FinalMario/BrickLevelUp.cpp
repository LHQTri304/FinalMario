#include "StationaryObject.h"

CQuestBrickLevelUp::CQuestBrickLevelUp(float x, float y) :CGameObject(x, y)
{
	itemsUp = new CItemsLevelUp(x, y);
	SetState(QUESTBRICK_STATE_WAIT);
}


void CQuestBrickLevelUp::Render()
{
	itemsUp->Render();

	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_QUEST_BRICK)->Render(x, y);

	if (GetState() == QUESTBRICK_STATE_ACTIVATED)
		animations->Get(ID_ANI_BLANK_BRICK)->Render(x, y);

	//RenderBoundingBox();
}

void CQuestBrickLevelUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CQuestBrickLevelUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	itemsUp->Update(dt, coObjects);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CQuestBrickLevelUp::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTBRICK_STATE_WAIT:
		break;
	case QUESTBRICK_STATE_ACTIVATED:
		itemsUp->SetState(COIN_STATE_ACTIVATED);
		break;
	}
}