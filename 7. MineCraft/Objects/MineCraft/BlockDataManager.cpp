#include "Framework.h"

BlockDataManager::BlockDataManager()
{
}

BlockDataManager::~BlockDataManager()
{
}

void BlockDataManager::LoadTable()
{
    ifstream loadFile("TextData/DataTable/BlockTable.csv");

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

        BlockData data;
        data.key = stoi(datas[0]);
        data.name = datas[1];
        data.modelName = datas[2];
        data.uiImage = datas[3];

        blockDatas[data.key] = data;
    }
}
