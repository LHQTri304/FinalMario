#include "InteractiveItems.h"

CButton::CButton(float x, float y) :CGameObject(x, y)
{
	this->iy = y;
	this->pixelMovingY = P_BUTTON_PIXEL_MOVE_Y;
	this->oneTimeActived = 0;
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
	//return (GetState() != P_BUTTON_STATE_WAIT);
	return 1;
}

void CButton::OnCollisionWith(LPCOLLISIONEVENT e)
{/*
	if (dynamic_cast<CMario*>(e->obj))
	{
		// touch >> Active
		if (GetState() == P_BUTTON_STATE_READY)
		{
			SetState(P_BUTTON_STATE_ACTIVATED);
		}
	}*/
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// The collition has some bug so let do another way
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mX, mY;
	mario->GetPosition(mX, mY);

	if (abs(mX - this->x) <= 7.5f && abs(mY - this->y) <= 5.5f
		&& GetState() == P_BUTTON_STATE_READY)
	{
		SetState(P_BUTTON_STATE_ACTIVATED);
		oneTimeActived++;
	}
		

	if (GetState() == P_BUTTON_STATE_SHOW)
	{
		if (y <= iy - pixelMovingY)
			SetState(P_BUTTON_STATE_READY);
		else
			y -= P_BUTTON_ACTIVATED_SPEED;
	}

	//Turn all GlassBrick into Coin
	if (GetState() == P_BUTTON_STATE_ACTIVATED && oneTimeActived < 2)
	{
		for (auto x : *coObjects)
		{
			if (dynamic_cast<CGlassBrick*>(x))
			{
				CGlassBrick* gb = dynamic_cast<CGlassBrick*>(x);
				gb->SetState(QUESTBRICK_STATE_ACTIVATED);
			}
		}
		SetState(P_BUTTON_STATE_NO_USE);
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
	if (GetState() == P_BUTTON_STATE_ACTIVATED || GetState() == P_BUTTON_STATE_NO_USE)
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
	case P_BUTTON_STATE_NO_USE:
		break;
	}
}