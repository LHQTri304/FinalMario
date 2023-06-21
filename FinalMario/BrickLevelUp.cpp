#include "StationaryObject.h"

void CQuestBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_QUEST_BRICK)->Render(x, y);

	if (GetState() == QUESTBRICK_STATE_ACTIVATED)
		animations->Get(ID_ANI_BLANK_BRICK)->Render(x, y);
}

void CQuestBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CQuestBrick::SetState(int state)
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