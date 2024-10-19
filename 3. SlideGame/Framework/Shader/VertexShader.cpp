#include "Framework.h"

VertexShader::VertexShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    
    D3DCompileFromFile(file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, &vertexShader);

    CreateInputLayout();
}

VertexShader::~VertexShader()
{
    vertexShader->Release();
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
    // reflection ������ ����, blob�� ���� VertexShader ������ �Ѱ��ְ�
    // ID ������ �ָ� �Ϸ�. ID ������ �������� ���ؼ��� ���̺귯�� �߰� �ʿ���
    D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
        IID_ID3D11ShaderReflection,(void**)&reflection);

    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
    inputLayouts.reserve(shaderDesc.InputParameters);

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask < 2) // Ÿ�� float �ΰ��
            elementDesc.Format = DXGI_FORMAT_R32_FLOAT;    
        else if(paramDesc.Mask < 4)// Ÿ�� float2 �ΰ��
            elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        else if (paramDesc.Mask < 8)// Ÿ�� float3 �ΰ��
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        else if (paramDesc.Mask < 16)// Ÿ�� float4 �ΰ��
            elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

        string temp = paramDesc.SemanticName;

        if (temp == "POSITION" && paramDesc.SemanticIndex==0)
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        inputLayouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout(inputLayouts.data(), inputLayouts.size(),
        blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);
}
