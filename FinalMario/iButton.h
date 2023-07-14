#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

class CButton : public CGameObject
{
protected:
	float iy;	//initial
	float pixelMovingY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable();	//Don't let anything change the button if it's not activated yet.
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CButton(float x, float y);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};