#define POLYRAM_OPENGL
#include "polyram.h"
#ifdef _AMD64_
#pragma comment ( lib, "..\\Build\\x64\\libPolyram.WinNT.lib" )
#else
#pragma comment ( lib, "..\\Build\\Win32\\libPolyram.WinNT.lib" )
#endif

class MyScene : public PRObject
{
public:
	void onInitialize ()
	{
		PRVersion version ( std::string ( ( const char * ) glGetString ( GL_VERSION ) ) );
		PRPrintLog ( "OpenGL Version: %d.%d", version.major, version.minor );
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

MAIN_FUNCTION_ATTR
MAIN_FUNCTION_RTTP MAIN_FUNCTION_NAME ( MAIN_FUNCTION_ARGS )
{
	MyScene scene;
	PRApplication application ( &scene, PRRendererType_OpenGL2, 1280, 720, std::string ( "Test" ) );
	application.run ();
}