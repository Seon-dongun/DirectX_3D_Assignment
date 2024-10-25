#include "Framework.h"
#include "GameManager.h"

#include "Scenes/GridScene.h"
#include "Scenes/RaidScene.h"


GameManager::GameManager()
{
    Create();
    
    SceneManager::Get()->Create("Grid", new GridScene());
    SceneManager::Get()->Create("Start", new RaidScene());

    SceneManager::Get()->Add("Grid");
    SceneManager::Get()->Add("Start");
}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    KEY->Update();
    Timer::Get()->Update();
    Environment::Get()->Update();

    SceneManager::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();

    Environment::Get()->Set();
    SceneManager::Get()->Render();

    Font::Get()->GetDC()->BeginDraw();

    Environment::Get()->SetPost();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 20 });

    Environment::Get()->GUIRender();
    SceneManager::Get()->GUIRender();

    Font::Get()->GetDC()->EndDraw();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Device::Get()->Present();
}

void GameManager::Create()
{
    Device::Get();
    Keyboard::Get();
    Timer::Get();
    Environment::Get();
    SceneManager::Get();

    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("Default", L"배민 을지로10년후체");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Device::Delete();
    Keyboard::Delete();
    Timer::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();
    SceneManager::Delete();
    Font::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}
