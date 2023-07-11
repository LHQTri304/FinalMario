#include "BlockEnterPipe.h"
#include "Mario.h"
#include "PlayScene.h"

void CBlockEnterPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	// Same idea with fakeHead
	left = x - FAKEHEAD_BBOX_WIDTH / 2;
	top = y - FAKEHEAD_BBOX_HEIGHT / 2;
	right = left + FAKEHEAD_BBOX_WIDTH;
	bottom = top + FAKEHEAD_BBOX_HEIGHT;
}

void CBlockEnterPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mX, mY;
	mario->GetPosition(mX, mY);

	if (abs(mX - this->x) <= 8.0f && abs(mY - this->y) <= 4.5f)
		mario->SetReadyToUsePipe(true);
	else
		mario->SetReadyToUsePipe(false);

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