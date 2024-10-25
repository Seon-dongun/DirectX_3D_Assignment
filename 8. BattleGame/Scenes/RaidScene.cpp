#include "Framework.h"
#include "RaidScene.h"

RaidScene::RaidScene()
{
	boss = new Boss();
	groot = new Groot();
	terrain = new Terrain();

	groot->SetEnemy(boss);
	boss->SetPlayer(groot);

	CAM->SetTarget(groot);
	CAM->TargetOptionLoad("Raid");
}

RaidScene::~RaidScene()
{
	delete groot;
	delete boss;
	delete terrain;
}

void RaidScene::Update()
{
	groot->Update();
	boss->Update();
}

void RaidScene::PreRender()
{
}

void RaidScene::Render()
{
	groot->Render();
	boss->Render();
	terrain->Render();
}

void RaidScene::PostRender()
{
	groot->PostRender();
	boss->PostRender();
}

void RaidScene::GUIRender()
{
	groot->GUIRender();
	boss->GUIRender();
}
