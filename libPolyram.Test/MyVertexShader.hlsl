struct VERTEX_IN
{
	float3 position : POSITION;
};

struct VERTEX_OUT
{
	float4 position : SV_POSITION;
};

VERTEX_OUT main ( VERTEX_IN input )
{
	VERTEX_OUT ret;
	ret.position = float4 ( input.position, 1 );
	return ret;
}