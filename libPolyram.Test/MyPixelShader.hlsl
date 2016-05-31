struct PIXEL_IN
{
	float4 position : SV_Position;
};

float4 main ( PIXEL_IN input ) : SV_TARGET
{
	return float4 ( 1, 1, 1, 1 );
}