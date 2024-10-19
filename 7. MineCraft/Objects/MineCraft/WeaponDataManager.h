#pragma once

struct WeaponData
{
    int key;
    string name;
    string modelName;
    string uiImage;
};

class WeaponDataManager : public Singleton<WeaponDataManager>
{
private:
    friend class Singleton;

    WeaponDataManager();
    ~WeaponDataManager();

public:
    void LoadTable();

    WeaponData GetWeaponData(int key) { return weaponDatas[key]; }
    int GetWeaponSize() { return weaponDatas.size(); }

private:
    map<int, WeaponData> weaponDatas;
};