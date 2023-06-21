#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INVISIBLE_BLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
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

void CGlassBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GLASS_BRICK)->Render(x, y);
}

void CGlassBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}


//*********************//

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


void CTrees::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREES)->Render(x, y);
}

void CBush::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BUSH)->Render(x, y);
}

void CCloud1::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD1)->Render(x, y);
}

void CCloud2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD2)->Render(x, y);
}

void CCloud3::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD3)->Render(x, y);
}

void CBlackEnd::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BLACK_END)->Render(x, y);
	animations->Get(ID_ANI_BORDER_END)->Render(x, y);
}