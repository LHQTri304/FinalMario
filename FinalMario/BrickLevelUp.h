#pragma once
#include "GameObject.h"

#define QUESTBRICK_STATE_WAIT 100
#define QUESTBRICK_STATE_ACTIVATED 200

class CQuestBrick : public CGameObject {
public:
	CQuestBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);
};