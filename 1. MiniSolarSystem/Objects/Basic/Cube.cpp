#include "Framework.h"

Cube::Cube(Float3 size)
{
    vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
    pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

    Float3 halfSize(size.x *0.5f, size.y *0.5f, size.z *0.5f);

    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 1, 0, 0);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 1, 0);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0, 0, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 1, 0);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 1, 0, 1);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 1, 1);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 1, 1);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0, 0, 0);

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexColor), vertices.size());

    indices =
    {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        1, 5, 3, 3, 5, 7,
        2,3,7,2,7,6,
        1,0,5,0,4,5,
        4,7,5,4,6,7,
        0,6,4,0,2,6
    };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
}

Cube::Cube(Float3 size,Float3 color)
{
    vertexShader = new VertexShader(L"Shaders/Tutorial.hlsl");
    pixelShader = new PixelShader(L"Shaders/Tutorial.hlsl");

    Float3 halfSize(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, color.x, color.y, color.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, color.x, color.y, color.z);

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexColor), vertices.size());

    indices =
    {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        1, 5, 3, 3, 5, 7,
        2,3,7,2,7,6,
        1,0,5,0,4,5,
        4,7,5,4,6,7,
        0,6,4,0,2,6
    };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
    delete vertexShader;
    delete pixelShader;
    delete vertexBuffer;
    delete indexBuffer;
    delete worldBuffer;
}

void Cube::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
