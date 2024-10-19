#include "Framework.h"

Store::Store(Steve* player) : player(player)
{
	ui = player->GetUI();
	SetTag("Store");
	body = new Cube();
	body->SetParent(this);

	localPosition = { -10,0,-10 };

	storePanel = new InventoryUI(L"Textures/UI/StorePanel.png");

	Load();

	startIcon = new Transform();
	startIcon->SetTag("StartIcon");
	startIcon->SetParent(storePanel);
	startIcon->SetLocalPosition({ -55,55,0 });

	for (int i = 0; i < WeaponDataManager::Get()->GetWeaponSize(); i++)
	{
		WeaponIcon* icon = new WeaponIcon(WeaponDataManager::Get()->GetWeaponData(i + 101));
		icon->SetParent(startIcon);
		icon->SetLocalPosition({ 0,i*(-30.0f),0});
		icon->SetLocalScale({ 20, 20, 1 });

		Button* btn = new Button(L"Textures/UI/BuyButton.png");
		btn->SetParent(icon);
		btn->SetLocalPosition({ 3,0,0 });
		btn->SetLocalScale({ 0.03,0.03,0.03 });
		btn->SetParamEvent(bind(&MineCraftUI::OnClickStoreBuyBtn, ui,placeholders::_1),icon);

		items.push_back({ icon,btn });
	}
	
	sellBtn = new Button(L"Textures/UI/BuyButton.png");
	sellBtn->SetTag("sellbtn");
	sellBtn->SetParent(startIcon);
	sellBtn->SetLocalPosition({ -7,-100,0 });
	sellBtn->SetLocalScale({ 0.5,0.5,0.5 });
	sellBtn->SetEvent(bind(&Store::OnClickSellBtn, this));

	body->UpdateWorld();
	UpdateWorld();
}

Store::~Store()
{
	delete body;
	delete storePanel;
}

void Store::Update()
{
	if (IsSphereCollision(player))
	{
		if (KEY->Down('Q'))
		{
			storePanel->SetActive(!storePanel->IsActive());
			ui->GetInvenPanel()->SetActive(!ui->GetInvenPanel()->IsActive());
		}
		if (storePanel->IsActive())
		{
			startIcon->UpdateWorld();
			for (itemLine icon : items)
			{
				icon.item->Update();
				icon.btn->Update();
			}

			sellBtn->Update();

			list<WeaponIcon*> tmp = ui->GetWeaponIcons();

			for (WeaponIcon* icon :tmp)
			{
				icon->Update();
			}

		}
	}
	else
	{
		storePanel->SetActive(false);
	}
}

void Store::Render()
{
	Collider::Render();
	body->Render();
}

void Store::PostRender()
{
	if (storePanel->IsActive())
	{
		storePanel->Render();
		for (itemLine icon : items)
		{
			icon.item->Render();
			icon.btn->Render();
			Font::Get()->RenderText("구매", { icon.btn->GetGlobalPosition().x+5, icon.btn->GetGlobalPosition().y});
		}
		sellBtn->Render();
		Font::Get()->RenderText("판매", { sellBtn->GetGlobalPosition().x + 20, sellBtn->GetGlobalPosition().y+10 });
		if(sellMode)
			Font::Get()->RenderText("판매 선택", { sellBtn->GetGlobalPosition().x + 300, sellBtn->GetGlobalPosition().y + 10 });
		else
			Font::Get()->RenderText("판매 선택되지 않음", { sellBtn->GetGlobalPosition().x + 300, sellBtn->GetGlobalPosition().y + 10 });


		list<WeaponIcon*> tmp = ui->GetWeaponIcons();
		for (WeaponIcon* icon : tmp)
		{
			icon->Render();
		}
	}
}

void Store::GUIRender()
{
	if (CAM->ContainSphere(localPosition, 1.0f) == false)
		return;

	Collider::GUIRender();

	Vector3 screenPos = CAM->WorldToScreen(localPosition + Vector3(0, 2.0f, 0));

	Font::Get()->RenderText("상점", {screenPos.x, screenPos.y});

	startIcon->GUIRender();
	sellBtn->GUIRender();
	for (itemLine icon : items)
	{
		icon.item->GUIRender();
		icon.btn->GUIRender();
	}
}

void Store::OnClickSellBtn()
{
	if (!sellMode)
	{
		sellBtn->GetMaterial()->SetDiffuseMap(L"Textures/UI/SellButtonDown.png");
	}
	else
	{
		sellBtn->GetMaterial()->SetDiffuseMap(L"Textures/UI/BuyButton.png");
	}

	sellMode = !sellMode;
}
