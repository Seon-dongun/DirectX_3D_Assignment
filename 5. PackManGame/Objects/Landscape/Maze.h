#pragma once
class Maze : public GameObject
{
private:
    typedef VertexUVNormal VertexType;

public:
    Maze();
    ~Maze();

    void Render();

    float GetHeight(const Vector3& pos);

private:
    void MakeMesh();
    void MakeNormal();

private:
    UINT width = 1, height = 1;

    Mesh<VertexType>* mesh;

    Texture* heightMap;

};