#pragma once

class ModelExporter
{
public:
    ModelExporter(string name, string file);
    ~ModelExporter();

    void ExportMaterial();
    void ExportMesh();

private:
    //Material
    void ReadMaterial();
    void WriterMaterial();
    string CreateTexture(string file);

    //Mesh
    void ReadMesh(aiNode* node);
    void WriteMesh();
    
private:
    Assimp::Importer* importer;
    const aiScene* scene;

    string name;

    vector<Material*> materials;
    vector<MeshData*> meshes;
};