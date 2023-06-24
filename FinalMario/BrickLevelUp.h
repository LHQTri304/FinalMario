#pragma once
#include "GameObject.h"
#include "iLevelUp.h"

#include "AllDefineStatus.h"

class CQuestBrickLevelUp : public CGameObject {
protected:
	BOOLEAN isActivated;
	CItemsLevelUp* itemsUp;
public:
	CQuestBrickLevelUp(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};