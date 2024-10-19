#include "Framework.h"

MineCraftUI::MineCraftUI()
{
    cursor = new Quad(L"Textures/UI/Cursor.png");
    cursor->SetLocalPosition({ CENTER_X, CENTER_Y, 0.0f });
    cursor->UpdateWorld();

    inventoryBtn = new Button(L"Textures/UI/InventoryIcon.png");
    inventoryBtn->SetTag("InventoryBtn");
    inventoryBtn->Load();
    inventoryBtn->SetEvent(bind(&MineCraftUI::OnClickInventoryBtn, this));

    inventoryPanel = new InventoryUI(L"Textures/UI/InventoryPanel.png");        


    for (int i = 0; i < BlockDataManager::Get()->GetBlockSize(); i++)
    {
        blockCount[i] = 0;
    }

    WeaponIcon* icon = new WeaponIcon(WeaponDataManager::Get()->GetWeaponData(101));
    icon->SetParent(inventoryPanel);
    icon->SetLocalScale({ 15,15,15 });
    icon->SetLocalPosition({ -72,-67,0 });
    icon->SetParamEvent(bind(&MineCraftUI::OnClickDeleteWeapon, this, placeholders::_1), icon);
    weaponIcons.push_back(icon);

    icon = new  WeaponIcon(WeaponDataManager::Get()->GetWeaponData(102));
    icon->SetParent(inventoryPanel);
    icon->SetLocalScale({ 15,15,15 });
    icon->SetLocalPosition({ -54,-67,0 });
    icon->SetParamEvent(bind(&MineCraftUI::OnClickDeleteWeapon, this, placeholders::_1), icon);
    weaponIcons.push_back(icon);
    // -77 -67 / 0.1 0.1 0.1          -54


    // 초기 위치 -72 -9 , 상하좌우 18 간격
}

MineCraftUI::~MineCraftUI()
{
    delete cursor;

    for (Block* block : blocks)
        delete block;

    for (BlockIcon* icon : blockIcons)
        delete icon;

    for (WeaponIcon* icon : weaponIcons)
        delete icon;

    delete inventoryBtn;
    delete inventoryPanel;
}

void MineCraftUI::Update()
{
    inventoryBtn->Update();
    inventoryPanel->Update();

    for (BlockIcon* icon : blockIcons)
        icon->UpdateWorld();

    int i = 0;
    for (WeaponIcon* icon : weaponIcons)
    {
        icon->SetLocalPosition({ -72.0f+(18.0f*i++),-67,0});
        icon->UpdateWorld();
    }
}

void MineCraftUI::PostRender()
{
    cursor->Render();

    inventoryPanel->Render();
    inventoryBtn->Render();

    if (inventoryPanel->IsActive())
    {
        for (BlockIcon* icon : blockIcons)
        {
            if (icon == nullptr)
                continue;

            icon->PostRender();

            Font::Get()->SetColor("Black");
            Font::Get()->SetStyle("배민 을지로10년후체");
            Font::Get()->RenderText(to_string(blockCount[icon->GetID()]), { icon->GetGlobalPosition().x + 17,icon->GetGlobalPosition().y - 6 });
        }

        for (WeaponIcon* icon : weaponIcons)
            icon->PostRender();
    }
}

void MineCraftUI::GUIRender()
{
    inventoryBtn->GUIRender();
    inventoryPanel->GUIRender();

    for (WeaponIcon* icon : weaponIcons)
        icon->GUIRender();
}

void MineCraftUI::Mining()
{
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y, 0));

    Block* block = BlockManager::Get()->Collision(ray);

    if (block == nullptr)
        return;

    blocks.push_back(block);
    int blockID = block->GetBlockData().key - 101;
    if (blockCount[blockID] == 0)
    {
        BlockIcon* icon = new BlockIcon(ToWString(block->GetBlockData().uiImage), blockID);

        int i, j;

        i = blockIcons.size() / MAX_ITEM_COL_LEN;
        j = blockIcons.size() - i * MAX_ITEM_COL_LEN;
        

        icon->SetLocalPosition({ -72+j*18.0f, -9+i*18.0f, 0 });
        icon->SetLocalScale({ 0.3,0.3,0.3 });
        icon->SetParent(inventoryPanel);

        blockIcons.push_back(icon);
    }

    blockCount[blockID]++;

}

void MineCraftUI::Build()
{
    if (blocks.size() == 0) return;

    Block* block = blocks.back();
    blocks.pop_back();

    BlockManager::Get()->AddBlock(block);

    int blockID = block->GetBlockData().key - 101;
    blockCount[blockID]--;

    list<BlockIcon*>::iterator it = blockIcons.begin();
    list<BlockIcon*>::iterator deleteIcon = blockIcons.end();

    if (blockCount[blockID] == 0)
    {
        for (; it != blockIcons.end(); it++)
        {
            if ((*it)->GetID() == blockID)
            {
                deleteIcon = it;
                break;
            }
        }
        blockIcons.erase(deleteIcon);
    }
}

void MineCraftUI::OnClickInventoryBtn()
{    
    inventoryPanel->SetActive(!inventoryPanel->IsActive());
}

void MineCraftUI::OnClickDeleteWeapon(void* object)
{
    if (!store->GetSellMode())
        return;

    WeaponIcon* deleteIcon = (WeaponIcon*)object;

    list<WeaponIcon*>::iterator it = weaponIcons.begin();

    for (; it != weaponIcons.end(); it++)
    {
        if (*it == deleteIcon)
        {
            weaponIcons.erase(it);
            break;
        }
    }

}

void MineCraftUI::OnClickStoreBuyBtn(void* object)
{
    WeaponIcon* tmp = (WeaponIcon*)object;
    WeaponData data = tmp->GetData();

    WeaponIcon* icon = new WeaponIcon(data);
    icon->SetParent(inventoryPanel);
    icon->SetLocalScale({ 15,15,15 });
    icon->SetLocalPosition({ (float)(18.0 * weaponIcons.size()-72),-67,0});
    icon->SetParamEvent(bind(&MineCraftUI::OnClickDeleteWeapon, this, placeholders::_1), icon);
    weaponIcons.push_back(icon);
}
