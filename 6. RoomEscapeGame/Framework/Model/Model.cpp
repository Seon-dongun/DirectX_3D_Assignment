#include "Framework.h"

Model::Model(string name,float colliderRadius,RoomEscapePlayer* playerInfo) : name(name),playerInfo(playerInfo)
{
    SetTag(name);

    ReadMaterial();
    ReadMesh();

    worldBuffer = new MatrixBuffer();

    collider = new SphereCollider(colliderRadius);

    collider->SetParent(this);

    Load();
}

Model::~Model()
{
    for (Material* material : materials)
        delete material;

    for (ModelMesh* mesh : meshes)
        delete mesh;

    delete worldBuffer;
    delete collider;
}

void Model::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    for (ModelMesh* mesh : meshes)
        mesh->Render();
}

void Model::Update()
{
    UpdateWorld();
    collider->UpdateWorld();
}

void Model::GUIRender()
{
    Transform::GUIRender();

    for (Material* material : materials)
        material->GUIRender();

    collider->GUIRender();
}

void Model::SetShader(wstring file)
{
    for (Material* material : materials)
        material->SetShader(file);
}

bool Model::IsPlayerGetItem()
{
    if (collider->IsSphereCollision(playerInfo))
        return true;
    return false;
}

void Model::ReadMaterial()
{
    string file = "Models/Materials/" + name + "/" + name + ".mats";

    BinaryReader* reader = new BinaryReader(file);
    if (reader->IsFailed()) assert(false);

    UINT size = reader->UInt();

    materials.reserve(size);

    FOR(size)
    {
        Material* material = new Material();
        material->Load(reader->String());
        materials.push_back(material);
    }

    delete reader;
}

void Model::ReadMesh()
{
    string file = "Models/Meshes/" + name + ".mesh";

    BinaryReader* reader = new BinaryReader(file);
    if (reader->IsFailed()) assert(false);

    UINT size = reader->UInt();

    meshes.reserve(size);

    FOR(size)
    {
        ModelMesh* mesh = new ModelMesh(reader->String());
        mesh->SetMaterial(materials[reader->UInt()]);

        UINT vertexCount = reader->UInt();
        ModelVertex* vertices = new ModelVertex[vertexCount];
        reader->Byte((void**)&vertices, sizeof(ModelVertex) * vertexCount);

        UINT indexCount = reader->UInt();
        UINT* indices = new UINT[indexCount];
        reader->Byte((void**)&indices, sizeof(UINT) * indexCount);

        mesh->CreateMesh(vertices, vertexCount, indices, indexCount);

        meshes.push_back(mesh);
    }

    delete reader;
}
