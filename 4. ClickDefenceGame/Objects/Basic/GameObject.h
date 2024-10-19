#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"Tutorial.hlsl");
    ~GameObject();

    void SetRender();

    Material* GetMaterial() { return material; }

protected:
    Material* material;    

    MatrixBuffer* worldBuffer;
};