#pragma once
class InventoryUI : public Quad
{
public:
    InventoryUI(wstring textureFile);
    ~InventoryUI();

    void Update();
    void Render();
    void GUIRender();

private:
    Vector3 offset;
    bool isDrag = false;
};