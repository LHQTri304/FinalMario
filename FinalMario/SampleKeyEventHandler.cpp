#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mVX = 0;
	float mVY = 0;

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (mario->GetIsReadyToUsePipe() && mario->GetEnterPipeDown() == 1)
		{
			mario->SetState(MARIO_STATE_ENTER_PIPE);
		}
		else
		{
			mario->SetState(MARIO_STATE_SIT);
		}
		break;
	case DIK_UP:
		if (mario->GetIsReadyToUsePipe() && mario->GetEnterPipeDown() == 0)
		{
			mario->SetState(MARIO_STATE_ENTER_PIPE);
		}
		break;
	case DIK_S:
		if (!mario->GetIsOnPlatform() && mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario->GetSpeed(mVX, mVY);
			if (mario->GetFlyable() == 1)
			{
				mario->SetSpeed(mVX, MARIO_FLYING_SPEED);
			}
			else if (mario->GetFlyable() == 0 && mVX != 0)
			{
				mario->SetSpeed(mVX, MARIO_FALLING_SPEED);
			}
			else
			{
				mario->SetState(MARIO_STATE_JUMP);
			}
		}
		else
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_A:
		mario->SetPressingKeyA(false);
		break;
	case DIK_DOWN:
		if (mario->GetState() != MARIO_STATE_ENTER_PIPE)
		{
			mario->SetState(MARIO_STATE_SIT_RELEASE);
		}
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetState() != MARIO_STATE_ENTER_PIPE)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_A))
			{
				mario->SetPressingKeyA(true);
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			}
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
			{
				mario->SetPressingKeyA(true);
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			}
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}