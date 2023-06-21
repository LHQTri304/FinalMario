#pragma once
#include "GameObject.h"

class CTrees : public CGameObject {
public:
	CTrees(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};

class CBush : public CGameObject {
public:
	CBush(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};

class CCloud1 : public CGameObject {
public:
	CCloud1(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};

class CCloud2 : public CGameObject {
public:
	CCloud2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};

class CCloud3 : public CGameObject {
public:
	CCloud3(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};

class CBlackEnd : public CGameObject {
public:
	CBlackEnd(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { return; }

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }
};