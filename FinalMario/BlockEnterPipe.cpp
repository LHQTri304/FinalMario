#include "StationaryObject.h"

void CBlockEnterPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FAKEHEAD_BBOX_WIDTH / 2;
	top = y - FAKEHEAD_BBOX_HEIGHT / 2;
	right = left + FAKEHEAD_BBOX_WIDTH;
	bottom = top + FAKEHEAD_BBOX_HEIGHT;
}

void CBlockEnterPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBlockEnterPipe::Render()
{
	RenderBoundingBox();
}

void CBlockEnterPipe::SetState(int state)
{
	CGameObject::SetState(state);
	return;
}