#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);	//ADD
	void RenderBoundingBox();
};

typedef CPlatform* LPPLATFORM;

//add... ColorBox
class CColorBox : public CGameObject
{
protected:
	int lengthWidth;				// Unit: cell 
	int lengthHeight;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTopLeft, spriteIdTopMid, spriteIdTopRight;
	int spriteIdMidLeft, spriteIdMidMid, spriteIdMidRight;
	int spriteIdBotLeft, spriteIdBotMid, spriteIdBotRight;

public:
	CColorBox(float x, float y,
		float cell_width, float cell_height, int length_width, int length_height,
		int sprite_id_top_left, int sprite_id_top_mid, int sprite_id_top_right,
		int sprite_id_mid_left, int sprite_id_mid_mid, int sprite_id_mid_right,
		int sprite_id_bot_left, int sprite_id_bot_mid, int sprite_id_bot_right) :CGameObject(x, y)
	{
		this->lengthWidth = length_width;
		this->lengthHeight = length_height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;

		this->spriteIdTopLeft = sprite_id_top_left;
		this->spriteIdTopMid = sprite_id_top_mid;
		this->spriteIdTopRight = sprite_id_top_right;

		this->spriteIdMidLeft = sprite_id_mid_left;
		this->spriteIdMidMid = sprite_id_mid_mid;
		this->spriteIdMidRight = sprite_id_mid_right;

		this->spriteIdBotLeft = sprite_id_bot_left;
		this->spriteIdBotMid = sprite_id_bot_mid;
		this->spriteIdBotRight = sprite_id_bot_right;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);	//ADD
	void RenderBoundingBox();
};

typedef CPlatform* LPPLATFORM;