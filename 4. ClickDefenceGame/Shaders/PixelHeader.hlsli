//PixelHeader.hlsli

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

cbuffer LightBuffer : register(b0)
{
	float3 lightDirection;
	
	float padding;
	
	float4 ambientLight;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 mDiffuse;
	float4 mSpecular;
	float4 mAmbient;
	float4 mEmissive;
	
	float shininess;
	int hasNormalMap;
}