#pragma once
#include "GameObject.h"

#include "AllDefineStatus.h"

class CQuestBrick : public CGameObject {
public:
	CQuestBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};

class CQuestBrickCoin : public CGameObject {
protected:
	CHidedCoin* hidedCoin;
public:
	CQuestBrickCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};