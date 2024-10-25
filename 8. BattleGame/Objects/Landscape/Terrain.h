#pragma once

class Terrain : public GameObject
{
private:
    typedef VertexUVNormal VertexType;

public:
    Terrain();
    ~Terrain();

    void Render();

    float GetHeight(const Vector3& pos);

private:
    void MakeMesh();
    void MakeNormal();

private:
    UINT width = 10, height = 10;

    Mesh<VertexType>* mesh;  

    Texture* heightMap;
};