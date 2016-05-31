#define POLYRAM_D3D11
#include "polyram.h"

class MyScene : public PRGame
{
public:

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );
		

	}

	void onDestroy ()
	{

	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_Direct3D11 );



		graphicsContext->dxgiSwapChain->Present ( 1, 0 );
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME ( MAIN_FUNC_ARGS )
{
	MyScene scene;
	std::string title ( "Test" );
	PRApplication application ( &scene, PRRendererType_Direct3D11, 1280, 720, title );
	application.run ();
}