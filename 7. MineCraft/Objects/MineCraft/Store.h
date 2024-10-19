#pragma once
struct itemLine
{
	WeaponIcon* item;
	Button* btn;
};

class Store : public BoxCollider
{
public:
	Store(Steve* player);
	~Store();

	void Update();
	void Render();
	void PostRender();

	void GUIRender();
	bool GetSellMode() { return sellMode; }
private:
	void OnClickSellBtn();
private:
	Cube* body;

	InventoryUI* storePanel;
	Steve* player;
	list<itemLine> items;

	Transform* startIcon;

	MineCraftUI* ui;

	Button* sellBtn;
	bool sellMode = false;
};