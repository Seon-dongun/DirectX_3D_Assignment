#pragma once

class Cube : public Transform
{
public:
    Cube(Float3 size = { 1, 1, 1 });
    Cube(Float3 size, wstring imageName);

    ~Cube();

    void Render();

private:
    Material* material;
    Mesh<VertexUV>* mesh;
    Mesh<VertexColor>* colorMesh;

    MatrixBuffer* worldBuffer;

    ID3D11ShaderResourceView* srv;
};