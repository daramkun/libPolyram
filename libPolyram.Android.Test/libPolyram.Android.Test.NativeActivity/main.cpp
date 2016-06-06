#define POLYRAM_OPENGL
#include "polyram.h"

class MyScene : public PRGame
{
public:
	void onInitialize ()
	{
		//std::string oglver ( ( const char * ) glGetString ( GL_VERSION ) );
		//PRVersion version ( oglver );
		//PRPrintLog ( "OpenGL Version: %d.%d", version.major, version.minor );
		PRPrintLog ( ( const char * ) glGetString ( GL_VERSION ) );
	}

	void onDestroy ()
	{

	}

	void onUpdate ( double dt )
	{

	}

	void onDraw ( double dt )
	{
		auto graphicsContext = static_cast< PRGraphicsContext_OpenGL* > ( PRApplication::sharedApplication ()->getGraphicsContext () );

		//float color [] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//graphicsContext->immediateContext->ClearRenderTargetView ( graphicsContext->renderTargetView, color );
		glClearColor ( 0, 0, 0, 1 );
		glClear ( GL_COLOR_BUFFER_BIT );

		//graphicsContext->dxgiSwapChain->Present ( 1, 0 );
		graphicsContext->swapBuffers ();
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME ( MAIN_FUNC_ARGS )
{
	MyScene scene;
	std::string title ( "Test" );
	PRApplication application ( &scene, PRRendererType_OpenGLES2, 720, 1280, title, state );
	application.run ();
}