#pragma once

class Model : public Transform
{
public:
    Model(string name,float colliderRadius,class RoomEscapePlayer* playerInfo);
    ~Model();

    void Render();
    void Update();
    void GUIRender();

    void SetShader(wstring file);
    bool IsPlayerGetItem();

private:
    void ReadMaterial();
    void ReadMesh();

protected:
    string name;
    vector<Material*> materials;
    vector<ModelMesh*> meshes;

    MatrixBuffer* worldBuffer;

    SphereCollider* collider;

    class RoomEscapePlayer* playerInfo;
};