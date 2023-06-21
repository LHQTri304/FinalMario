#include "StationaryObject.h"


//*********************//


void CTrees::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREES)->Render(x, y);
}

void CBush::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BUSH)->Render(x, y);
}

void CCloud1::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD1)->Render(x, y);
}

void CCloud2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD2)->Render(x, y);
}

void CCloud3::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD3)->Render(x, y);
}

void CBlackEnd::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BLACK_END)->Render(x, y);
	animations->Get(ID_ANI_BORDER_END)->Render(x, y);
}