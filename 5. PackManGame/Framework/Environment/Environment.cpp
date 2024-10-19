#include "Framework.h"

Environment::Environment()
{
    CreateProjection();
    CreateState();

    SetViewport();

    mainCamera = new Camera();
    lightBuffer = new LightBuffer();
    uiViewBuffer = new ViewBuffer();

    SetCandleLight();
}

Environment::~Environment()
{
    delete projectionBuffer;
    delete uiViewBuffer;

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

    if (ImGui::TreeNode("LightOption"))
    {
        if (ImGui::Button("Add"))
            lightBuffer->GetData()->lightCount++;

        FOR(lightBuffer->GetData()->lightCount)
            EditLight(&lightBuffer->GetData()->lights[i], i);

        ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->GetData()->ambientLight);
        ImGui::ColorEdit3("AmbientCeil", (float*)&lightBuffer->GetData()->ambientCeil);

        ImGui::TreePop();
    }
}

void Environment::Set()
{
    rasterizerState[isWireMode]->SetState();
    blendState[0]->SetState();

    mainCamera->SetView();
    lightBuffer->SetPS(0);

    projectionBuffer->Set(perspective);
    projectionBuffer->SetVS(2);
}

void Environment::SetPost()
{
    blendState[1]->SetState();

    uiViewBuffer->SetVS(1);
    projectionBuffer->Set(orthographic);
    projectionBuffer->SetVS(2);
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

void Environment::CreateProjection()
{
    perspective = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        (float)WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

    orthographic = XMMatrixOrthographicOffCenterLH(0.0f, WIN_WIDTH,
        0.0f, WIN_HEIGHT, -1.0f, 1.0f);

    projectionBuffer = new MatrixBuffer();
}

void Environment::CreateState()
{
    samplerState = new SamplerState();
    samplerState->SetState();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);
}

void Environment::SetCandleLight()
{
    lightBuffer->GetData()->lightCount += 4;
    lightBuffer->GetData()->lights[1].type = 1;
    lightBuffer->GetData()->lights[1].position = { 108,40,132 };
    lightBuffer->GetData()->lights[1].attentionIntensity = 0.2f;
    lightBuffer->GetData()->lights[1].range = 48;

    lightBuffer->GetData()->lights[2].type = 1;
    lightBuffer->GetData()->lights[2].position = { 110,15,306 };
    lightBuffer->GetData()->lights[2].attentionIntensity = 3;
    lightBuffer->GetData()->lights[2].range = 40;

    lightBuffer->GetData()->lights[3].type = 1;
    lightBuffer->GetData()->lights[3].position = { 160,15,233 };
    lightBuffer->GetData()->lights[3].attentionIntensity = 2.5;
    lightBuffer->GetData()->lights[3].range = 35;

    lightBuffer->GetData()->lights[4].type = 1;
    lightBuffer->GetData()->lights[4].position = { 63,15,217 };
    lightBuffer->GetData()->lights[4].attentionIntensity = 2.5;
    lightBuffer->GetData()->lights[4].range = 35;
}

void Environment::EditLight(LightBuffer::Light* light, int index)
{
    string label = "Light_" + to_string(index);

    if (ImGui::TreeNode(label.c_str()))
    {
        ImGui::Checkbox("Active", (bool*)&light->isActive);

        const char* list[] = { "Directional", "Point", "Spot" };
        ImGui::Combo("Type", &light->type, list, 3);

        ImGui::ColorEdit3("Color", (float*)&light->color);
        ImGui::SliderFloat3("Directoin", (float*)&light->direction, -1, 1);
        ImGui::SliderFloat3("Position", (float*)&light->position, -100, 500);
        ImGui::SliderFloat("Range", (float*)&light->range, 1, 300);
        ImGui::SliderFloat("Inner", (float*)&light->inner, 1, 180);
        ImGui::SliderFloat("Outer", (float*)&light->outer, 1, 180);
        ImGui::SliderFloat("AttentionIntensity", (float*)&light->attentionIntensity, 0.1f, 3.0f);

        ImGui::TreePop();
    }
}
