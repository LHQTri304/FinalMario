#include "ColorBox.h"

void CCOLOR_BOX::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COLOR_BOX)->Render(x, y);

	//RenderBoundingBox();
}

void CCOLOR_BOX::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COLOR_BOX_BBOX_WIDTH / 2;
	t = y - COLOR_BOX_BBOX_HEIGHT / 2;
	r = l + COLOR_BOX_BBOX_WIDTH;
	b = t + COLOR_BOX_BBOX_HEIGHT;
}