#pragma once

class VertexShader : public Shader
{
private:
    friend class Shader;

    VertexShader(wstring file);
    ~VertexShader();

public:
    void Set() override;

private:
    void CreateInputLayout();

private:
    ID3D11VertexShader* vertexShader;    
    ID3D11InputLayout* inputLayout;

    // vertexShader의 정보를 얻어올 수 있는 요소
    // Tutorial.hlsl을 보았을 때, VertexInput 으로 들어가는 정보를 얻을 수 있음. 
    // 사용한 시멘틱, 변수, 변수의 타입의 정보를 얻을 수 있다.
    ID3D11ShaderReflection* reflection;
};