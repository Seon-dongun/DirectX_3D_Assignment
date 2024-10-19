#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Quad(Float2 size = { 1, 1 });
    Quad(wstring textureFile);
    ~Quad();
        
    void Render();
    void ChangeTexture(wstring textureFile);

private:
    void MakeMesh();
private:
    Mesh<VertexType>* mesh;

    Float2 size;
};