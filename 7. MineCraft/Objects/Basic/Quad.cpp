#include "Framework.h"

Quad::Quad(Float2 size) : size(size)
{
    tag = "Quad";

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::Quad(wstring textureFile)
    : GameObject(L"Basic/Texture.hlsl")
{
    Texture* texture = Texture::Add(textureFile);
    material->SetDiffuseMap(textureFile);
    size = texture->GetSize();

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

Quad::~Quad()
{
    delete mesh;
}

void Quad::Render()
{
    if (!IsActive()) return;

    SetRender();

    mesh->Draw();
}

bool Quad::IsContainPos(Vector3 screenPos)
{
    float left = GetGlobalPosition().x - GetSize().x * 0.5f;
    float right = GetGlobalPosition().x + GetSize().x * 0.5f;
    float top = GetGlobalPosition().y + GetSize().y * 0.5f;
    float bottom = GetGlobalPosition().y - GetSize().y * 0.5f;

    if (screenPos.x > left && screenPos.x < right)
    {
        if (screenPos.y > bottom && screenPos.y < top)
            return true;
    }

    return false;
}

void Quad::MakeMesh()
{
    Float2 halfSize(size.x * 0.5f, size.y * 0.5f);

    vector<VertexType>& vertices = mesh->GetVertices();
    
    vertices.emplace_back(-halfSize.x, -halfSize.y, 0, 0, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, 0, 0, 0);
    vertices.emplace_back(+halfSize.x, -halfSize.y, 0, 1, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, 0, 1, 0);

    for (VertexType& vertex : vertices)
    {
        vertex.normal = { 0, 0, -1 };
        vertex.tangent = { 1, 0, 0 };
    }


    vector<UINT>& indices = mesh->GetIndices();

    indices =
    {
        0, 1, 2, 2, 1, 3,     
    };
}
