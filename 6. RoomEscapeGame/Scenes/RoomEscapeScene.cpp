#include "Framework.h"
#include "RoomEscapeScene.h"

RoomEscapeScene::RoomEscapeScene()
{
	player = new RoomEscapePlayer(0.2f);

	room = new Quad();
	door = new Model("Door",1.0f,player);
	chest = new Model("Chest",50.0f,player);
	table = new Model("Table",0.5f,player);
}

RoomEscapeScene::~RoomEscapeScene()
{
	delete room;
	delete door;
	delete chest;
	delete table;
	delete player;
}

void RoomEscapeScene::ItemStateUpdate()
{
	if (KEY->Down('Q') && !isGetChestKey && table->IsPlayerGetItem())
	{
		isGetChestKey = true;
		player->GetItemUI()->ChangeTexture(L"Textures/UI/ItemUIGetChestKey.png");

		const char* message;
		const char* title;

		message = "Á¤Ã¼ºÒ¸íÀÇ ¿­¼è¸¦ È¹µæÇß´Ù.";
		title = "¾ÆÀÌÅÛ È¹µæ";

		MessageBoxA(NULL, message, title, MB_OK);
	}


	if (KEY->Down('Q') && !isGetEscapeKey && chest->IsPlayerGetItem())
	{
		if (!isGetChestKey)
		{
			const char* message;
			const char* title;

			message = "¼±¹Ý ¼­¶øÀÌ ±»°Ô Àá°ÜÀÖ´Ù..";
			title = "´ÝÈù ¼­¶ø";

			MessageBoxA(NULL, message, title, MB_OK);
		}
		else
		{
			isGetEscapeKey = true;
			player->GetItemUI()->ChangeTexture(L"Textures/UI/ItemUIGetEscapeKey.png");

			const char* message;
			const char* title;

			message = "ÀÛÀº ¿­¼è¸¦ È¹µæÇß´Ù. ¹®¿¡ µü ¸ÂÀ» °Í °°´Ù";
			title = "¾ÆÀÌÅÛ È¹µæ";

			MessageBoxA(NULL, message, title, MB_OK);
		}
	}

	if (KEY->Down('Q') && door->IsPlayerGetItem())
	{
		if (isGetEscapeKey)
		{
			const char* message;
			const char* title;

			message = "¹æÅ»Ãâ ¼º°ø! ÃàÇÏÇÕ´Ï´Ù!!";
			title = "¹æÅ»Ãâ ¼º°ø";

			MessageBoxA(NULL, message, title, MB_OK);

			PostQuitMessage(0);
		}
		else
		{
			const char* message;
			const char* title;

			message = "¹®À» ¿­±â À§ÇÑ ¿­¼è°¡ ÇÊ¿äÇÏ´Ù..";
			title = "´ÝÈù ¹®";

			MessageBoxA(NULL, message, title, MB_OK);
		}
	}
}


void RoomEscapeScene::Update()
{
	ItemStateUpdate();

	player->Update();

	room->UpdateWorld();
	door->Update();
	chest->Update();
	table->Update();
}

void RoomEscapeScene::PreRender()
{
}

void RoomEscapeScene::Render()
{
	player->Render();

	room->Render();
	door->Render();
	chest->Render();
	table->Render();
}

void RoomEscapeScene::PostRender()
{
	player->PostRender();
}

void RoomEscapeScene::GUIRender()
{
	room->GUIRender();
	door->GUIRender();
	chest->GUIRender();
	table->GUIRender();
}
