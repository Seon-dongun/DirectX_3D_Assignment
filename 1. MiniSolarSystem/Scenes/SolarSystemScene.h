#pragma once

class SolarSystemScene : public Scene
{
private:
    const UINT HEIGHT = 10;

public:
    SolarSystemScene();
    ~SolarSystemScene();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;
    void GUIRender() override;

private:
    vector<Cube*> cubes;
    vector<Line*> lines;
    vector<Line*> xz;

    MatrixBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;
};