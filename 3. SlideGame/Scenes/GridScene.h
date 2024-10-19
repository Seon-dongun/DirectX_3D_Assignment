#pragma once

class GridScene : public Scene
{
private:
    const int MAX_SIZE = 100;

public:
    GridScene();
    ~GridScene();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;
    void GUIRender() override;
private:
    void MakeMesh();
private:
    Material* material;
    Mesh<VertexColor>* mesh;
    MatrixBuffer* worldBuffer;

    UINT width, height;
};