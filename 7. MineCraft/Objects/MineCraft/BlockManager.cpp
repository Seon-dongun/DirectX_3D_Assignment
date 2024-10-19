#include "BlockManager.h"
#include "Framework.h"

BlockManager::BlockManager()
{
}

BlockManager::~BlockManager()
{
    for (Block* block : blocks)
        delete block;
}

void BlockManager::Update()
{
    for (Block* block : blocks)
        block->Update();
}

void BlockManager::Render()
{
    for (Block* block : blocks)
        block->Render();
}

void BlockManager::GUIRender()
{
    for (Block* block : blocks)
        block->GUIRender();
}

void BlockManager::CreateBlocks(UINT x, UINT y, UINT z)
{
    for (UINT i = 0; i < x; i++)
    {
        for (UINT j = 0; j < y; j++)
        {
            for (UINT k = 0; k < z; k++)
            {
                int random = 100 + MATH->Random(0, BlockDataManager::Get()->GetBlockSize()) + 1;
                BlockData data = BlockDataManager::Get()->GetBlockData(random);

                Block* block = new Block(data);
                block->SetLocalPosition(Vector3(i, j, k));
                block->Update();

                blocks.push_back(block);
            }
        }
    }
}

float BlockManager::GetHeight(const Vector3& pos)
{
    Ray ray(pos, Vector3::Down());
    Contact contact;

    float maxHeight = 0.0f;

    for (Block* block : blocks)
    {
        if (block->IsRayCollision(ray, &contact))
        {
            if (contact.hitPoint.y > maxHeight)
                maxHeight = contact.hitPoint.y;
        }
    }

    return maxHeight;
}

void BlockManager::PushCollider(Collider* collider)
{
    Block* collisionBlock = nullptr;

    for (Block* block : blocks)
    {
        if (block->IsCollision(collider))
        {
            Vector3 direction = block->GetDirection(collider->GetGlobalPosition());

            if (direction == block->GetUp())
                continue;

            collider->Translate(direction * PUSH_SPEED * DELTA);
        }
    }
}

void BlockManager::AddBlock(Block* block)
{
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y, 0));

    float minDistance = FLT_MAX;
    Contact contact;
    Vector3 hitPoint;

    list<Block*>::iterator iter = blocks.begin();
    list<Block*>::iterator collisionBlock = blocks.end();

    for (; iter != blocks.end(); iter++)
    {
        if ((*iter)->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                collisionBlock = iter;
                hitPoint = contact.hitPoint;
            }
        }
    }

    if (collisionBlock == blocks.end())
        return;

    Block* hitBlock = *collisionBlock;
    Vector3 direction = hitBlock->GetDirection(hitPoint);
    Vector3 pos = hitBlock->GetGlobalPosition() + direction;

    block->SetLocalPosition(pos);
    block->Update();
    blocks.push_back(block);
}

Block* BlockManager::Collision(const Ray& ray)
{
    float minDistance = FLT_MAX;
    Contact contact;

    list<Block*>::iterator iter = blocks.begin();
    list<Block*>::iterator collisionBlock = blocks.end();

    for (; iter != blocks.end(); iter++)
    {
        if ((*iter)->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                collisionBlock = iter;
            }
        }
    }

    if (collisionBlock == blocks.end())
        return nullptr;

    Block* block = *collisionBlock;
    blocks.erase(collisionBlock);

    return block;
}
