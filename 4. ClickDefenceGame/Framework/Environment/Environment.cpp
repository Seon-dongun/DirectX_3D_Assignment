#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateState();

    SetViewport();

    mainCamera = new Camera();
    lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete projectionBuffer;

    delete samplerState;

    delete rasterizerState[0];
    delete rasterizerState[1];

    delete mainCamera;
    delete lightBuffer;
}

void Environment::Update()
{
    if (KEY->Down(VK_F1))
        isWireMode = !isWireMode;

    mainCamera->Update();
}

void Environment::GUIRender()
{
    mainCamera->GUIRender();

    ImGui::SliderFloat3("LightDirectoin", (float*)&lightBuffer->GetData()->lightDirection, -1, 1);    
    ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->GetData()->ambientLight);
}

void Environment::Set()
{
    rasterizerState[isWireMode]->SetState();

    mainCamera->SetView();
    lightBuffer->SetPS(0);
}

void Environment::SetViewport(UINT width, UINT height)
{
    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = width;
    viewPort.Height = height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort);
}

void Environment::SetPerspective()
{
}

void Environment::CreateProjection()
{    
    projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

    projectionBuffer = new MatrixBuffer();

    projectionBuffer->Set(projection);
    projectionBuffer->SetVS(2);
}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->SetState();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);
}
