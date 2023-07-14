#pragma once
#include "GameObject.h"
#include "iCoin.h"

#include "AllDefineStatus.h"

class CGlassBrick : public CGameObject {
protected:
	BOOLEAN isActivated;
	CCoin* coin;
	ULONGLONG activated_start;
public:
	CGlassBrick(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return !isActivated; }
	virtual void SetState(int state);
};