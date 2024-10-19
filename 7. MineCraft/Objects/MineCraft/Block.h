#pragma once

class Block : public BoxCollider
{
public:
    Block(BlockData data);
    ~Block();

    void Update();
    void Render();
    void GUIRender();

    Vector3 GetDirection(Vector3 point);

    BlockData GetBlockData() { return data; }

private:
    BlockData data;
    Model* model;
};