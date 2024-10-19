#include "Framework.h"
#include "DefenceGameScene.h"

DefenceGameScene::DefenceGameScene()
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemys.push_back(new Enemy());
		enemys[i]->SetLocalPosition({ (float)(i* ENEMY_COUNT), 0, (float)(i * ENEMY_COUNT) });
	}
}

DefenceGameScene::~DefenceGameScene()
{
	for (Enemy* enemy : enemys)
		delete enemy;
}

void DefenceGameScene::Update()
{
	if (IsGameOver())
	{
		const char* message;
		const char* title;
	
		message = "게임 오버! 다시 도전하세요!";
		title = "게임 오버";
		
		MessageBoxA(NULL, message, title, MB_OK);

		PostQuitMessage(0); 
	}

	if (IsGameClear())
	{
		const char* message;
		const char* title;

		message = "게임 클리어! 축하합니다!!";
		title = "게임 클리어";

		MessageBoxA(NULL, message, title, MB_OK);

		PostQuitMessage(0);
	}


	Ray ray = CAM->ScreenPointToRay(mousePos);

	Contact contact;

	for (Enemy* enemy : enemys)
	{
		if (enemy->GetIsActive())
		{
			if (KEY->Down(VK_LBUTTON))
			{
				if (enemy->IsRayCollision(ray, &contact))
				{
					enemy->SetIsActive(false);
					break;
				}
			}
		}
	}

	for (Enemy* enemy : enemys)
	{
		if (enemy->GetIsActive())
		{
			enemy->MoveToTarget();
		}
	}
}

void DefenceGameScene::PreRender()
{
}

void DefenceGameScene::Render()
{
	for (Enemy* enemy : enemys)
	{
		if (enemy->GetIsActive())
		{
			enemy->GetSphere()->Render();
		}
	}
}

void DefenceGameScene::PostRender()
{
}

void DefenceGameScene::GUIRender()
{
	for (Enemy* enemy : enemys)
	{
		if (enemy->GetIsActive())
			enemy->GUIRender();
	}
}

bool DefenceGameScene::IsGameOver()
{
	for (Enemy* enemy : enemys)
	{
		if ((enemy->GetLocalPosition()-CAM->GetLocalPosition()).Length() < 3.0f)
			return true;
	}
	return false;
}

bool DefenceGameScene::IsGameClear()
{
	for (Enemy* enemy : enemys)
	{
		if (enemy->GetIsActive())
			return false;
	}
	return true;
}
