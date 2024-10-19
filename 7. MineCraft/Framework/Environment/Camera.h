#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void GUIRender();

    void SetView();

    Ray ScreenPointToRay(Vector3 screenPoint);
    Vector3 WorldToScreen(Vector3 worldPos);

    bool ContainPoint(Vector3 point);
    bool ContainSphere(Vector3 center, float radius);

private:
    void FreeMode();

    void Frustum();

private:
    ViewBuffer* viewBuffer;
    Matrix view;
    Matrix projection;

    float moveSpeed = 20.0f;
    float rotSpeed = 3.0f;

    Vector3 prevMousePos;

    Vector3 planes[6];
    float a, b, c, d;
};