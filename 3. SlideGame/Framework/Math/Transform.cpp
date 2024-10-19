#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
    world = XMMatrixTransformation(pivot, XMQuaternionIdentity(),
        localScale, pivot,
        XMQuaternionRotationRollPitchYawFromVector(localRotation),
        localPosition);

    if (parent)
        world *= parent->world;
}

void Transform::Translate(Vector3 direction)
{
    localPosition += direction;
}

void Transform::Rotate(Vector3 direction)
{
    localRotation += direction;
}
