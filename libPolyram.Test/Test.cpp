#define POLYRAM_OPENGL
#include "polyram.h"

class MyScene : public PRGame
{
public:
	GLuint vertexArrayObject, vertexBufferObject;
	int vertexCount;

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );
		
		glGenVertexArrays ( 1, &vertexArrayObject );
		glBindVertexArray ( vertexArrayObject );

		PRModelGenerator * gen = new PRModelGenerator ( std::string ( "bunny.obj" ), PRModelTexCoord_ST );
		glGenBuffers ( 1, &vertexBufferObject );
		glBindBuffer ( GL_ARRAY_BUFFER, vertexBufferObject );

		glBufferData ( GL_ARRAY_BUFFER, gen->getDataSize (), gen->getData (), GL_STATIC_DRAW );

		int index = 0;
		glEnableVertexAttribArray ( index );
		glVertexAttribPointer ( index, 3, GL_FLOAT, false, 0, 0 );
		++index;
		if ( gen->getProperties () & PRModelProperty_Normal )
		{
			glEnableVertexAttribArray ( index );
			glVertexAttribPointer ( index, 3, GL_FLOAT, false, 0, ( void* ) ( sizeof ( float ) * 3 ) );
		}
		if ( gen->getProperties () & PRModelProperty_TexCoord )
		{
			glEnableVertexAttribArray ( index );
			glVertexAttribPointer ( index, 2, GL_FLOAT, false, 0,
				( void* ) ( sizeof ( float ) * ( gen->getProperties () & PRModelProperty_Normal ? 6 : 3 ) ) );
		}

		glBindVertexArray ( 0 );

		delete gen;
	}

	void onDestroy ()
	{
		glDeleteVertexArrays ( 1, &vertexArrayObject );
		glDeleteBuffers ( 1, &vertexBufferObject );
	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );

		glBindVertexArray ( vertexArrayObject );
		glDrawArrays ( GL_TRIANGLES, 0, vertexCount );

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