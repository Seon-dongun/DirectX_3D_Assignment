#pragma once

class Model : public Transform
{
public:
    Model(string name);
    ~Model();

    void Render();
    void GUIRender();

    void SetShader(wstring file);

    Matrix GetNodeTransform(string name) { return nodeTransforms[name]; }

private:
    void ReadMaterial();
    void ReadMesh();

    void MakeBoneTransforms();

protected:
    string name;
    vector<Material*> materials;
    vector<ModelMesh*> meshes;
    vector<NodeData> nodes;
    vector<BoneData> bones;

    MatrixBuffer* worldBuffer;

    vector<Matrix> boneTransforms;
    map<string, Matrix> nodeTransforms;
    map<string, UINT> boneMap;
};