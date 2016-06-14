#define POLYRAM_OPENGL
#include "polyram.h"

class MyScene : public PRGame
{
public:

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );
		
		PRModelGenerator * gen = new PRModelGenerator ( std::string ( "bunny.obj" ), PRModelTexCoord_ST );

		delete gen;
	}

	void onDestroy ()
	{

	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );



		graphicsContext->swapBuffers ();
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME ( MAIN_FUNC_ARGS )
{
	try {
		MyScene scene;
		std::string title ( "Test" );
		PRApplication application ( &scene, PRRendererType_OpenGL2, 1280, 720, title );
		application.run ();
	} catch ( std::exception & ex ) {
		PRPrintLog ( ex.what () );
	}
}