#include "Framework.h"

Cube::Cube(Float3 size)
{
    material = new Material(L"Basic/Grid.hlsl");
    colorMesh = new Mesh<VertexColor>();

    Float3 halfSize(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    vector<VertexColor>& vertices = colorMesh->GetVertices();
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0.1,0.1,0.1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0.1,0.1,0.1);

    vector<UINT>& indices = colorMesh->GetIndices();

    indices =
    {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        4,5,6,6,5,7,
        //Right
        8,9,10,10,9,11,
        //Left
        12,13,14,14,13,15,
        //Back
        16,17,18,18,17,19,
        //Down
        20,21,22,22,21,23
    };

    colorMesh->CreateMesh();

    worldBuffer = new MatrixBuffer();
}

Cube::Cube(Float3 size, wstring imageName)
{
    material = new Material(L"Tutorial.hlsl");
    mesh = new Mesh<VertexUV>();

    Float3 halfSize(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    vector<VertexUV>& vertices = mesh->GetVertices();
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 0);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 0);

    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0, 0);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 0);

    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0, 0);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 1, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 1, 0);

    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 0);
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 1, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 1, 0);

    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 0);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 0);

    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 1);
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 0);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 0);

    vector<UINT>& indices = mesh->GetIndices();

    indices =
    {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        4,5,6,6,5,7,
        //Right
        8,9,10,10,9,11,
        //Left
        12,13,14,14,13,15,
        //Back
        16,17,18,18,17,19,
        //Down
        20,21,22,22,21,23
    };

    mesh->CreateMesh();

    worldBuffer = new MatrixBuffer();

    ScratchImage image;
    LoadFromWICFile(imageName.c_str(), WIC_FLAGS_NONE,
        nullptr, image);

    CreateShaderResourceView(DEVICE, image.GetImages(),
        image.GetImageCount(), image.GetMetadata(), &srv);
}

Cube::~Cube()
{
    delete mesh;
    delete worldBuffer;

    srv->Release();
}


void Cube::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    DC->PSSetShaderResources(0, 1, &srv);

    material->Set();
    if(mesh!=nullptr)
        mesh->Draw();
    if(colorMesh!=nullptr)
        colorMesh->Draw();
}
