#pragma once

class BlockManager : public Singleton<BlockManager>
{
private:
    const float PUSH_SPEED = 5.0f;

private:
    friend class Singleton;

    BlockManager();
    ~BlockManager();

public:
    void Update();
    void Render();
    void GUIRender();

    void CreateBlocks(UINT x, UINT y, UINT z);

    float GetHeight(const Vector3& pos);
    void PushCollider(Collider* collider);
    void AddBlock(Block* block);
    Block* Collision(const Ray& ray);

private:
    list<Block*> blocks;
};