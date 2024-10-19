#pragma once

class SlideGameScene : public Scene
{
private:
    const UINT HEIGHT = 10;

public:
    SlideGameScene();
    ~SlideGameScene();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;
    void GUIRender() override;

    void CubeShuffle();
    void GameClear();

private:
    vector<Cube*> cubes;
    int loc[9];
    float speed = 1.0f;
};