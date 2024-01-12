struct PS_INPUT
{
	float2 texCoord : TEXCOORD;
	float4 inPos : SV_POSITION;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objsamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT psIn) : SV_TARGET
{

	float3 pixelColor = objTexture.Sample(objsamplerState, psIn.texCoord);
	return float4(pixelColor, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
}