#include "Enemies.h"

CFakeHead::CFakeHead(float x, float y) :CGameObject(x, y)
{
	this->ay = FAKEHEAD_GRAVITY;
}

void CFakeHead::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FAKEHEAD_BBOX_WIDTH / 2;
	top = y - FAKEHEAD_BBOX_HEIGHT / 2;
	right = left + FAKEHEAD_BBOX_WIDTH;
	bottom = top + FAKEHEAD_BBOX_HEIGHT;
}

void CFakeHead::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFakeHead::OnCollisionWith(LPCOLLISIONEVENT e)
{
	return;
}

void CFakeHead::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFakeHead::Render()
{
	//int aniId = ID_ANI_FAKEHEAD;

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFakeHead::SetState(int state)
{
	CGameObject::SetState(state);
	return;
}