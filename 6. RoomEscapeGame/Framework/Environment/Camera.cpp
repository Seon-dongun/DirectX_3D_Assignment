#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new ViewBuffer();
    viewBuffer->SetVS(1);
    viewBuffer->SetPS(1);

    prevMousePos = mousePos;    

    Load();
}

Camera::~Camera()
{
    Save();

    delete viewBuffer;
}


void Camera::Update()
{
    projection = Environment::Get()->GetProjection();

    FreeMode();

    UpdateWorld();
}

void Camera::GUIRender()
{
    if (ImGui::TreeNode("CameraOption"))
    {
        ImGui::DragFloat("MoveSpeed", &moveSpeed);
        ImGui::DragFloat("RotSpeed", &rotSpeed);

        ImGui::TreePop();
    }
}

void Camera::SetView()
{
    view = XMMatrixInverse(nullptr, world);
    viewBuffer->Set(view, world);

    viewBuffer->SetVS(1);
    viewBuffer->SetPS(1);
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
    Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);

    Float2 point;
    point.x = (screenPoint.x / screenSize.x) * 2.0f - 1.0f;
    point.y = (screenPoint.y / screenSize.y) * 2.0f - 1.0f;

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);

    screenPoint.x = point.x / temp._11;
    screenPoint.y = point.y / temp._22;
    screenPoint.z = 1.0f;

    screenPoint = XMVector3TransformNormal(screenPoint, world);

    return Ray(localPosition, screenPoint.GetNormalized());
}

void Camera::FreeMode()
{
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos;

    if (KEY->Press(VK_RBUTTON))
    {
        if (KEY->Press('W'))
            Translate(GetForward() * moveSpeed * DELTA);
        if (KEY->Press('S'))
            Translate(GetBack() * moveSpeed * DELTA);
        if (KEY->Press('A'))
            Translate(GetLeft() * moveSpeed * DELTA);
        if (KEY->Press('D'))
            Translate(GetRight() * moveSpeed * DELTA);
        if (KEY->Press('Q'))
            Translate(GetDown() * moveSpeed * DELTA);
        if (KEY->Press('E'))
            Translate(GetUp() * moveSpeed * DELTA);

        Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
        Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);
    }
}

