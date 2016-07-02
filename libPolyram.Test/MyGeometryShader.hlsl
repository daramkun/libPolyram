struct GSOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

#define PI				3.1415926

[maxvertexcount(11)]
void main( point GSOutput input [ 1 ], inout LineStream<GSOutput> output )
{
	GSOutput element;
	element.color = input [ 0 ].color;

	for ( int i = 1; i <= 10; ++i )
	{
		float angle = ( PI * 2 ) / 10 * i;
		float4 offset = float4 ( cos ( angle ) * 0.25, -sin ( angle ) * 0.4, 0, 0 );
		element.position = input [ 0 ].position + offset;
		output.Append ( element );
		
		if ( i % 2 == 0 )
			output.RestartStrip ();
	}
}