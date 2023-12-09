struct Output
{
	float3 color : COLOR;
	float4 position : SV_POSITION;
};

Output main( float3 pos : POSITION, float3 col : COLOR )
{
	Output output;
	output.position = float4(pos, 1.0f);
	output.color = col;
	return output;
}