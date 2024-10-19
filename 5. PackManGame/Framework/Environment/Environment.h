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
    void SetPost();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

    void CreateProjection();
    void CreateState();

    Matrix GetProjection() { return perspective; }
    Camera* GetMainCamera() { return mainCamera; }

    LightBuffer::Light* GetLight(int index) { return &lightBuffer->GetData()->lights[index]; }

    void SetCandleLight();
private:
    void EditLight(LightBuffer::Light* light, int index);

private:
    MatrixBuffer* projectionBuffer;
    ViewBuffer* uiViewBuffer;

    SamplerState* samplerState;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

    Camera* mainCamera;

    LightBuffer* lightBuffer;

    Matrix perspective;
    Matrix orthographic;

    bool isWireMode = false;
};