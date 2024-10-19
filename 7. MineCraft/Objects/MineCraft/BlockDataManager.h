#pragma once

struct BlockData
{
    int key;
    string name;
    string modelName;
    string uiImage;
};

class BlockDataManager : public Singleton<BlockDataManager>
{
private:
    friend class Singleton;

    BlockDataManager();
    ~BlockDataManager();

public:
    void LoadTable();

    BlockData GetBlockData(int key) { return blockDatas[key]; }
    int GetBlockSize() { return blockDatas.size(); }

private:
    map<int, BlockData> blockDatas;
};