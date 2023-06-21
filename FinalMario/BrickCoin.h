#pragma once
#include "GameObject.h"
#include "iCoin.h"

#include "AllDefineStatus.h"

class CQuestBrickCoin : public CGameObject {
protected:
	int countDownTest = 100;

	CCoin* hidedCoin;
public:
	CQuestBrickCoin(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};