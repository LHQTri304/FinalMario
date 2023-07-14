#pragma once
#include "GameObject.h"
#include "iLevelUp.h"

#include "AllDefineStatus.h"


class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CDirtBrick : public CGameObject {
public:
	CDirtBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CButtonBrick : public CGameObject {
protected:
	BOOLEAN isActivated;
	CItemsLevelUp* itemsUp;
public:
	CButtonBrick(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};