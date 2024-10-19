#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity();
}

void Transform::GUIRender()
{
    if (ImGui::TreeNode((tag + "_Transform").c_str()))
    {
        string temp = tag + "_Pos";
        ImGui::DragFloat3(temp.c_str(), (float*)&localPosition, 0.1f);

        temp = tag + "_Rot";
        Float3 rot;
        rot.x = XMConvertToDegrees(localRotation.x);
        rot.y = XMConvertToDegrees(localRotation.y);
        rot.z = XMConvertToDegrees(localRotation.z);

        ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

        localRotation.x = XMConvertToRadians(rot.x);
        localRotation.y = XMConvertToRadians(rot.y);
        localRotation.z = XMConvertToRadians(rot.z);

        temp = tag + "_Scale";
        ImGui::DragFloat3(temp.c_str(), (float*)&localScale, 0.1f);

        if (ImGui::Button("Save"))
            Save();

        ImGui::SameLine();

        if (ImGui::Button("Load"))
            Load();

        ImGui::TreePop();
    }
}

void Transform::UpdateWorld()
{
    world = XMMatrixTransformation(pivot, XMQuaternionIdentity(),
        localScale, pivot,
        XMQuaternionRotationRollPitchYawFromVector(localRotation),
        localPosition);

    if (parent)
        world *= parent->world;

    XMStoreFloat4x4(&matWorld, world);
    right = Vector3(matWorld._11, matWorld._12, matWorld._13);
    up = Vector3(matWorld._21, matWorld._22, matWorld._23);
    forward = Vector3(matWorld._31, matWorld._32, matWorld._33);

    XMMatrixDecompose(globalScale.GetValue(),
        globalRotation.GetValue(), globalPosition.GetValue(), world);
}

void Transform::Translate(Vector3 direction)
{
    localPosition += direction;
}

void Transform::Rotate(Vector3 direction)
{
    localRotation += direction;
}

void Transform::Save()
{
    BinaryWriter* writer = new BinaryWriter("TextData/Transforms/" + tag + ".srt");

    writer->Vector(localPosition);
    writer->Vector(localRotation);
    writer->Vector(localScale);
    writer->Vector(pivot);

    delete writer;
}

void Transform::Load()
{
    BinaryReader* reader = new BinaryReader("TextData/Transforms/" + tag + ".srt");

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    localPosition = reader->Vector();
    localRotation = reader->Vector();
    localScale = reader->Vector();
    pivot = reader->Vector();

    UpdateWorld();

    delete reader;
}
