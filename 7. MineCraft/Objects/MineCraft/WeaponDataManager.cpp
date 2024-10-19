#include "Framework.h"

WeaponDataManager::WeaponDataManager()
{
}

WeaponDataManager::~WeaponDataManager()
{
}

void WeaponDataManager::LoadTable()
{
    ifstream loadFile("TextData/DataTable/WeaponTable.CSV");

    string temp;

    bool isFirstLine = true;

    while (!loadFile.eof())
    {
        loadFile >> temp;

        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        vector<string> datas = SplitString(temp, ",");

        WeaponData data;
        data.key = stoi(datas[0]);
        data.name = datas[1];
        data.modelName = datas[2];
        data.uiImage = datas[3];

        weaponDatas[data.key] = data;
    }
}
