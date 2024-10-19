#pragma once

class RobotModelScene : public Scene
{
private:
    const UINT HEIGHT = 10;

public:
    RobotModelScene();
    ~RobotModelScene();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;
    void GUIRender() override;

private:
    vector<Cube*> cubes;

    MatrixBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;
};