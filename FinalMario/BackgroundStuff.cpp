#include "StationaryObject.h"

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

void CSTART_SCENE::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_START_SCENE)->Render(x, y);
}

void COVER_SCENE::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_OVER_SCENE)->Render(x, y);
}

void CLevelMapScene::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	switch (num)
	{
	case 4:
		animations->Get(ID_ANI_LEVEL_MAP_SCENE_4)->Render(x, y);
		break;
	case 3:
		animations->Get(ID_ANI_LEVEL_MAP_SCENE_3)->Render(x, y);
		break;
	case 2:
		animations->Get(ID_ANI_LEVEL_MAP_SCENE_2)->Render(x, y);
		break;
	default:
		animations->Get(ID_ANI_LEVEL_MAP_SCENE_1)->Render(x, y);
		break;
	}
}