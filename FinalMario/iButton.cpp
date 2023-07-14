#include "InteractiveItems.h"

CButton::CButton(float x, float y) :CGameObject(x, y)
{
	this->iy = y;
	this->pixelMovingY = P_BUTTON_PIXEL_MOVE_Y;
	SetState(P_BUTTON_STATE_WAIT);
}

void CButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - P_BUTTON_BBOX_WIDTH / 2;
	top = y - P_BUTTON_BBOX_HEIGHT / 2;
	right = left + P_BUTTON_BBOX_WIDTH;
	bottom = top + P_BUTTON_BBOX_HEIGHT;
}

int CButton::IsCollidable()
{
	return (GetState() != P_BUTTON_STATE_WAIT);
}

void CButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//Only collides with mario
	if ((e->nx != 0 || e->ny != 0) && e->obj->IsBlocking())
	{
		if (dynamic_cast<CMario*>(e->obj))
		{
			// touch >> Active
			if (GetState() == P_BUTTON_STATE_READY)
			{
				SetState(P_BUTTON_STATE_ACTIVATED);
			}
		}
	}
	else
		return;
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetState() == P_BUTTON_STATE_SHOW)
	{
		if (y <= iy - pixelMovingY)
			SetState(P_BUTTON_STATE_READY);
		else
			y -= P_BUTTON_ACTIVATED_SPEED;
	}

	//Turn all GlassBrick into Coin
	if (GetState() == P_BUTTON_STATE_ACTIVATED)
	{
		for (auto x : *coObjects)
		{
			if (dynamic_cast<CGlassBrick*>(x))
			{
				x->SetState(QUESTBRICK_STATE_ACTIVATED);
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CButton::Render()
{
	int aniId = ID_ANI_INVISIBLE;

	if (GetState() == P_BUTTON_STATE_SHOW || GetState() == P_BUTTON_STATE_READY)
	{
		aniId = ID_ANI_P_BUTTON_SHOW;
	}
	if (GetState() == P_BUTTON_STATE_ACTIVATED)
	{
		aniId = ID_ANI_P_BUTTON_ACTIVATED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case P_BUTTON_STATE_WAIT:
		break;
	case P_BUTTON_STATE_SHOW:
		break;
	case P_BUTTON_STATE_READY:
		break;
	case P_BUTTON_STATE_ACTIVATED:
		break;
	}
}