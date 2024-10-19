#pragma once
class WeaponIcon : public Button
{
public:
	WeaponIcon(WeaponData data);
	~WeaponIcon();

	WeaponData GetData() { return data; }
	void PostRender();
private:
	WeaponData data;
};