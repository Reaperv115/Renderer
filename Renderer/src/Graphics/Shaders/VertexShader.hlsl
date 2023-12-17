struct VS_INPUT
{
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float2 texcoord : TEXCOORD;
	float4 position : SV_POSITION;
};

cbuffer WorldMat
{
	matrix worldMat;
};

VS_OUTPUT main(VS_INPUT vsIn)
{
	VS_OUTPUT output;
	output.position = mul(float4(vsIn.pos, 1.0f), worldMat);
	output.texcoord = vsIn.texCoord;
	return output;
}