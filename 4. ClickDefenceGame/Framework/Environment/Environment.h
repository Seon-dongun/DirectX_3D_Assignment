#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

public:
    void Update();
    void GUIRender();

    void Set();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    void SetPerspective();

    void CreateProjection();
    void CreateState();

    Matrix GetProjection() { return projection; }
    Camera* GetMainCamera() { return mainCamera; }
private:
    MatrixBuffer* projectionBuffer;

    SamplerState* samplerState;
    RasterizerState* rasterizerState[2];

    Camera* mainCamera;

    LightBuffer* lightBuffer;

    Matrix projection;
    bool isWireMode = false;
};