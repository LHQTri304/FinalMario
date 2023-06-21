#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

#pragma region Platform
void CPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPlatform::Render()
{
	if (this->length <= 0) return; 
	float xx = x; 
	CSprites * s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, y);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length>1)
		s->Get(this->spriteIdEnd)->Draw(xx, y);

	//RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight;
}

//ADD
int CPlatform::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
#pragma endregion


#pragma region ColorBox
//add... ColorBox
void CColorBox::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CColorBox::Render()
{
	if (this->lengthWidth <= 0 || this->lengthHeight <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();	

	//#1:	Draw the top of the box...
	s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->lengthWidth - 1; i++)
	{
		s->Get(this->spriteIdTopMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (lengthWidth > 1)
		s->Get(this->spriteIdTopRight)->Draw(xx, yy);

	//#2:	Draw the middle of the box...
	for (int i = 0; i < this->lengthHeight - 2; i++)	//	-2 = - begin & end
	{
		xx = x;
		yy += this->cellHeight;

		s->Get(this->spriteIdMidLeft)->Draw(xx, yy);
		xx += this->cellWidth;

		for (int i = 1; i < this->lengthWidth - 1; i++)
		{
			s->Get(this->spriteIdMidMid)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (lengthWidth > 1)
			s->Get(this->spriteIdMidRight)->Draw(xx, yy);
	}

	//#3:	Draw the bottom of the box...
	xx = x;
	yy += this->cellHeight;

	s->Get(this->spriteIdBotLeft)->Draw(xx, yy);
	xx += this->cellWidth;

	for (int i = 1; i < this->lengthWidth - 1; i++)
	{
		s->Get(this->spriteIdBotMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (lengthWidth > 1)
		s->Get(this->spriteIdBotRight)->Draw(xx, yy);

	//RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthWidth;
	b = t + this->cellHeight;
}

//ADD
int CColorBox::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}
#pragma endregion


#pragma region BigDirt_Pipe
void CBigDirt_Pipe::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CBigDirt_Pipe::Render()
{
	if (this->lengthWidth <= 0 || this->lengthHeight <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	//#1:	Draw the top of the box...
	s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->lengthWidth - 1; i++)
	{
		s->Get(this->spriteIdTopMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (lengthWidth > 1)
		s->Get(this->spriteIdTopRight)->Draw(xx, yy);

	//#2:	Draw the middle of the box...
	for (int i = 0; i < this->lengthHeight - 2; i++)	//	-2 = - begin & end
	{
		xx = x;
		yy += this->cellHeight;

		s->Get(this->spriteIdMidLeft)->Draw(xx, yy);
		xx += this->cellWidth;

		for (int i = 1; i < this->lengthWidth - 1; i++)
		{
			s->Get(this->spriteIdMidMid)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (lengthWidth > 1)
			s->Get(this->spriteIdMidRight)->Draw(xx, yy);
	}

	//#3:	Draw the bottom of the box...
	xx = x;
	yy += this->cellHeight;

	s->Get(this->spriteIdBotLeft)->Draw(xx, yy);
	xx += this->cellWidth;

	for (int i = 1; i < this->lengthWidth - 1; i++)
	{
		s->Get(this->spriteIdBotMid)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (lengthWidth > 1)
		s->Get(this->spriteIdBotRight)->Draw(xx, yy);

	//RenderBoundingBox();
}

void CBigDirt_Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthWidth;
	b = t + this->cellHeight * this->lengthHeight;
}

//ADD
int CBigDirt_Pipe::IsDirectionColliable(float nx, float ny)
{
	return 1;
}
#pragma endregion