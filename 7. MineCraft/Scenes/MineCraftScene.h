#pragma once

class MineCraftScene : public Scene
{
public:
    MineCraftScene();
    ~MineCraftScene();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;
    void GUIRender() override;

private:
    Steve* steve;
    Store* store;
};