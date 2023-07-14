#include "StationaryObject.h"

void CBrick::Render()
{
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CDirtBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DIRT_BRICK)->Render(x, y);
}

void CDirtBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}



#pragma region P-Button Brick
CButtonBrick::CButtonBrick(float x, float y) :CGameObject(x, y)
{
	this->isActivated = false;
	itemsUp = new CItemsLevelUp(x, y);
	SetState(QUESTBRICK_STATE_WAIT);
}


void CButtonBrick::Render()
{
	if (itemsUp->GetKind() == ITEMS_LEVELUP_KIND_MUSHROOM)	// Mushroom render behind the Brick
		itemsUp->Render();

	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_QUEST_BRICK)->Render(x, y);

	if (GetState() == QUESTBRICK_STATE_ACTIVATED)
		animations->Get(ID_ANI_BLANK_BRICK)->Render(x, y);

	if (itemsUp->GetKind() == ITEMS_LEVELUP_KIND_LEAF)	// Leaf render in front of the Brick
		itemsUp->Render();

	//RenderBoundingBox();
}

void CButtonBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CButtonBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	itemsUp->Update(dt, coObjects);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CButtonBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTBRICK_STATE_WAIT:
		break;
	case QUESTBRICK_STATE_ACTIVATED:
		if (!isActivated)
		{
			itemsUp->SetState(COIN_STATE_ACTIVATED);
			isActivated = true;
		}
		break;
	}
}
#pragma endregion