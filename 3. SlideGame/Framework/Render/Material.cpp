#include "Framework.h"

Material::Material(wstring shaderFile)
{
    SetShader(shaderFile);
}

Material::~Material()
{
}

void Material::Set()
{
    vertexShader->Set();
    pixelShader->Set();
}

void Material::SetShader(wstring shaderFile)
{
    vertexShader = Shader::AddVS(shaderFile);
    pixelShader = Shader::AddPS(shaderFile);
}
