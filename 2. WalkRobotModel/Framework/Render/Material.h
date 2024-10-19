#pragma once

class Material
{
public:
    Material(wstring shaderFile);
    ~Material();

    void Set();

    void SetShader(wstring shaderFile);

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;
};