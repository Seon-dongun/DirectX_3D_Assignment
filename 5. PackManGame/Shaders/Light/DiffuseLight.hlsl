//DiffuseLight
#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = input.uv;
	
	output.normal = normalize(mul(input.normal, (float3x3)world));
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 albedo = diffuseMap.Sample(samp, input.uv);
	
	float3 normal = normalize(input.normal);
	float3 light = normalize(lightDirection);
	
	float diffsue = dot(normal, -light);
	
	return diffuseMap.Sample(samp, input.uv) * diffsue;
}