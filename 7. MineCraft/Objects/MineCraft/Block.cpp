#include "Framework.h"
#include "Block.h"

Block::Block(BlockData data) : data(data)
{
    SetTag(data.name + "_Collider");

    model = new Model(data.modelName);
    model->SetParent(this);
    model->Load();
}

Block::~Block()
{
    delete model;
}

void Block::Update()
{
    //if (CAM->ContainSphere(localPosition, 0.5f) == false)
    //    return;

    UpdateWorld();
    model->UpdateWorld();
}

void Block::Render()
{
    if (CAM->ContainSphere(localPosition, 0.5f) == false)
        return;

    model->Render();
    Collider::Render();
}

void Block::GUIRender()
{
    if (CAM->ContainSphere(localPosition, 0.5f) == false)
        return;

    Vector3 screenPos = CAM->WorldToScreen(localPosition + Vector3(0, 0.5f, 0));

    Font::Get()->RenderText(data.name, { screenPos.x, screenPos.y });

    model->GUIRender();
    Transform::GUIRender();
}

Vector3 Block::GetDirection(Vector3 point)
{
    Vector3 direction = (point - GetGlobalPosition()).GetNormalized();

    Vector3 planes[6];
    planes[0] = GetRight();
    planes[1] = GetLeft();
    planes[2] = GetUp();
    planes[3] = GetDown();
    planes[4] = GetForward();
    planes[5] = GetBack();

    float minAngle = FLT_MAX;
    Vector3 result;

    for (Vector3 plane : planes)
    {
        float dot = Vector3::Dot(plane, direction);
        float angle = abs(acos(dot));

        if (angle < minAngle)
        {
            minAngle = angle;
            result = plane;
        }
    }

    return result;
}
