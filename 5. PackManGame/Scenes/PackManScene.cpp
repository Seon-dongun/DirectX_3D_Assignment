#include "Framework.h"
#include "PackManScene.h"

PackManScene::PackManScene()
{
	maze = new Maze();
	packman = new Packman(2.0f);
	coinManager = new CoinManager(packman);

	packman->SetLocalPosition({ 110,0,120});
	packman->SetMaze(maze);
}

PackManScene::~PackManScene()
{
	delete maze;
	delete packman;
	delete coinManager;
}


void PackManScene::Update()
{
	if (IsGameClear())
	{
		const char* message;
		const char* title;

		message = "게임 클리어! 축하합니다!!";
		title = "게임 클리어";

		MessageBoxA(NULL, message, title, MB_OK);

		PostQuitMessage(0);
	}

	packman->Update();
	coinManager->Update();
}

void PackManScene::PreRender()
{
}

void PackManScene::Render()
{
	maze->Render();
	packman->Render();
	coinManager->Render();
}

void PackManScene::PostRender()
{
}

void PackManScene::GUIRender()
{
	maze->GUIRender();
	packman->GUIRender();
}

bool PackManScene::IsGameClear()
{
	if (coinManager->GetCoinCount() == 0)
		return true;
	return false;
}
