#pragma once

class ModelMesh
{
public:
    ModelMesh(string name);
    ~ModelMesh();

    void Render();

    void CreateMesh(void* vertices, UINT vertexCount,
        void* indices, UINT indexCount);

    void SetMaterial(Material* material) { this->material = material; }

private:
    string name;

    Material* material;
    Mesh<ModelVertex>* mesh;
};