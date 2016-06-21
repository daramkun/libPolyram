#pragma pack_matrix(row_major) 

struct VERTEX_IN
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
};

struct VERTEX_OUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

cbuffer MyConstantBuffer : register ( b0 )
{
	matrix world : WORLD;
	matrix projection : PROJECTION;
};

VERTEX_OUT main ( VERTEX_IN input )
{
	VERTEX_OUT ret;
	ret.position = float4 ( input.position, 1 );
	ret.position = mul ( ret.position, world );
	ret.position = mul ( ret.position, projection );
	ret.texcoord = float2 ( input.texcoord.x, 1 - input.texcoord.y );
	return ret;
}