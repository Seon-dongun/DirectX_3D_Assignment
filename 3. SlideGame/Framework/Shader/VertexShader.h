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

    // vertexShader�� ������ ���� �� �ִ� ���
    // Tutorial.hlsl�� ������ ��, VertexInput ���� ���� ������ ���� �� ����. 
    // ����� �ø�ƽ, ����, ������ Ÿ���� ������ ���� �� �ִ�.
    ID3D11ShaderReflection* reflection;
};