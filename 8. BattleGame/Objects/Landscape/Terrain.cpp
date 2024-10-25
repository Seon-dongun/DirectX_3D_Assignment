#include "Framework.h"

Terrain::Terrain()
{
    tag = "Terrain";

    material->SetShader(L"Light/Light.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");
    
    heightMap = Texture::Add(L"Textures/HeightMaps/HeightMap.png");

    mesh = new Mesh<VertexType>();
    MakeMesh();
    MakeNormal();
    mesh->CreateMesh();
}

Terrain::~Terrain()
{
    delete mesh;
}

void Terrain::Render()
{
    SetRender();

    mesh->Draw();
}

float Terrain::GetHeight(const Vector3& pos)
{
    int x = (int)pos.x;
    int z = (int)pos.z;

    if (x < 0 || x >= width - 1) return 0.0f;
    if (z < 0 || z >= height - 1) return 0.0f;

    UINT index[4];
    index[0] = width * z + x;
    index[1] = width * (z + 1) + x;
    index[2] = width * z + x + 1;
    index[3] = width * (z + 1) + x + 1;

    vector<VertexType>& vertices = mesh->GetVertices();

    Vector3 p[4];
    FOR(4)
        p[i] = vertices[index[i]].pos;

    float u = pos.x - p[0].x;
    float v = pos.z - p[0].z;

    Vector3 result;

    if (u + v <= 1.0f)
    {
        result = ((p[2] - p[0]) * u + (p[1] - p[0]) * v) + p[0];
    }
    else
    {
        u = 1.0f - u;
        v = 1.0f - v;

        result = ((p[1] - p[3]) * u + (p[2] - p[3]) * v) + p[3];
    }

    return result.y;
}

void Terrain::MakeMesh()
{
    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    vector<Float4> pixels;
    heightMap->ReadPixels(pixels);

    //Vertices
    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height);
    for (UINT z = 0; z < height; z++)
    {
        for (UINT x = 0; x < width; x++)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0.0f, (float)z };
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);

            UINT index = width * z + x;
            vertex.pos.y = pixels[index].x * 20.0f;

            vertices.push_back(vertex);
        }
    }

    //Indices
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; z++)
    {
        for (UINT x = 0; x < width - 1; x++)
        {
            indices.push_back(width * z + x);//0
            indices.push_back(width * (z + 1) + x);//1
            indices.push_back(width * z + x + 1);//2

            indices.push_back(width * z + x + 1);//2
            indices.push_back(width * (z + 1) + x);//1
            indices.push_back(width * (z + 1) + x + 1);//3
        }
    }
}

void Terrain::MakeNormal()
{
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT>& indices = mesh->GetIndices();

    FOR(indices.size() / 3)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        Vector3 normal = Vector3::Cross(e0, e1).GetNormalized();

        vertices[index0].normal += normal;
        vertices[index1].normal += normal;
        vertices[index2].normal += normal;
    }
}
