struct PIXEL_IN
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
};

Texture2D mySampler;
SamplerState samplerState;

float4 main ( PIXEL_IN input ) : SV_TARGET
{
	return float4 ( float3 ( 1, 1, 1 ) - mySampler.Sample ( samplerState, input.texcoord ).xyz, 1 );
}