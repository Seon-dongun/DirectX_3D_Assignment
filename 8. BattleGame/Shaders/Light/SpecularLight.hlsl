//SpecularLight
#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

PixelInput VS(VertexUVNormal input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = input.uv;
	
	output.normal = normalize(mul(input.normal, (float3x3) world));
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 albedo = diffuseMap.Sample(samp, input.uv);
	
	float3 normal = normalize(input.normal);
	float3 light = normalize(lightDirection);
	float3 viewDir = normalize(input.worldPos - invView._41_42_43);
	
	float diffsue = saturate(dot(normal, -light));
	float4 specular = 0;
	
	if (diffsue > 0)
	{
		//Phong Shading
		float3 reflection = normalize(reflect(light, normal));
		specular = saturate(dot(-reflection, viewDir));
		
		float4 specularIntensity = specularMap.Sample(samp, input.uv);
		
		specular = pow(specular, shininess) * specularIntensity;
	}
	
	return diffuseMap.Sample(samp, input.uv) * diffsue + specular;
}