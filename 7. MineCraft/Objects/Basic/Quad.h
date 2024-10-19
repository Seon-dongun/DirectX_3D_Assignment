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

    bool IsContainPos(Vector3 screenPos);

    Float2 GetSize()
    {
        return { GetGlobalScale().x * size.x, GetGlobalScale().y * size.y };
    }

private:
    void MakeMesh();

private:
    Mesh<VertexType>* mesh;

    Float2 size;
};