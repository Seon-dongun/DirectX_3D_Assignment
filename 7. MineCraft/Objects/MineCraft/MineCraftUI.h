#pragma once
#define MAX_ITEM_COL_LEN 9
#define MAX_ITEM_ROW_LEN 3
#define MAX_EQUIP_WEAPON 4
class MineCraftUI
{
public:
    MineCraftUI();
    ~MineCraftUI();

    void Update();
    void PostRender();
    void GUIRender();

    void Mining();
    void Build();

    void OnClickStoreBuyBtn(void* object);

    void SetStore(class Store* store) { this->store = store; }

    list<WeaponIcon*>& GetWeaponIcons() {
        return weaponIcons;
    }

    InventoryUI* GetInvenPanel() { return inventoryPanel; }
private:
    void OnClickInventoryBtn();
    void OnClickDeleteWeapon(void* object);
private:
    Quad* cursor;

    list<Block*> blocks;
    map<int, int> blockCount;

    Button* inventoryBtn;
    InventoryUI* inventoryPanel;

    list<BlockIcon*> blockIcons;
    list<WeaponIcon*> weaponIcons;

    list<WeaponIcon*> equipWeaponIcons;

    class Store* store;
};