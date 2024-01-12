#pragma pack_matrix(row_major)

struct VS_INPUT
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float2 texcoord : TEXCOORD;
	float4 position : SV_POSITION;
};

cbuffer WorldMat : register(b0)
{
	float4x4 mat;
};

VS_OUTPUT main(VS_INPUT vsIn)
{
	VS_OUTPUT output;
	vsIn.pos = mul(vsIn.pos, mat);

	output.position = vsIn.pos;
	output.texcoord = vsIn.texCoord;
	return output;
}