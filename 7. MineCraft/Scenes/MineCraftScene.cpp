#include "Framework.h"
#include "MineCraftScene.h"

MineCraftScene::MineCraftScene()
{
    BlockDataManager::Get()->LoadTable();
    WeaponDataManager::Get()->LoadTable();
    BlockManager::Get()->CreateBlocks(10, 3, 10);

    steve = new Steve();
    store = new Store(steve);

    steve->GetUI()->SetStore(store);
}

MineCraftScene::~MineCraftScene()
{
    BlockManager::Delete();
    BlockDataManager::Delete();
    WeaponDataManager::Delete();

    delete steve;
    delete store;
}

void MineCraftScene::Update()
{
    //BlockManager::Get()->Update();
    BlockManager::Get()->PushCollider(steve);
    steve->Update();    
    store->Update();
}

void MineCraftScene::PreRender()
{
}

void MineCraftScene::Render()
{
    BlockManager::Get()->Render(); 
    steve->Render();
    store->Render();
}

void MineCraftScene::PostRender()
{
    steve->PostRender();
    store->PostRender();
}

void MineCraftScene::GUIRender()
{   
    //BlockManager::Get()->GUIRender();

    steve->GUIRender();
    store->GUIRender();
}
