#include "Framework.h"

InventoryUI::InventoryUI(wstring textureFile)
    : Quad(textureFile)
{
    SetTag("InventoryPanel");
    Load();

    SetActive(false);
}

InventoryUI::~InventoryUI()
{
    Save();
}

void InventoryUI::Update()
{
    if (KEY->Down(VK_LBUTTON) && IsContainPos(mousePos))
    {
        isDrag = true;
        offset = GetGlobalPosition() - mousePos;
    }

    if (isDrag && KEY->Press(VK_LBUTTON))
    {
        SetLocalPosition(mousePos + offset);
    }

    if (KEY->Up(VK_LBUTTON))
        isDrag = false;

    UpdateWorld();
}

void InventoryUI::Render()
{
    Quad::Render();
}

void InventoryUI::GUIRender()
{
    Transform::GUIRender();
}


