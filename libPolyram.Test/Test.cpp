#define POLYRAM_OPENGL
#include "polyram.h"

class MyScene : public PRGame
{
public:
	GLuint vertexArrayObject, vertexBufferObject;
	int vertexCount;
	GLuint vertexShader, fragmentShader, program;

public:
	void onInitialize ()
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );

		GLchar buffer [ 1024 ];
		GLint bufferLength;

		const GLchar * vertexShaderString = "#version 330\n"
			"in vec3 in_pos;\n"
			"in vec3 in_nor;\n"
			"in vec4 in_col;\n"
			"uniform mat4 world;\n"
			"uniform mat4 view;\n"
			"uniform mat4 proj;\n"
			"uniform vec4 worldLightPosition;\n"
			"out vec4 out_col;\n"
			"void main () {\n"
			"	gl_Position = vec4 ( in_pos, 1 );\n"
			"	gl_Position = world * gl_Position;\n"
			"	\n"
			"	vec3 lightDir = gl_Position.xyz - worldLightPosition.xyz;\n"
			"	lightDir = normalize ( lightDir );\n"
			"	\n"
			"	gl_Position = view * gl_Position;\n"
			"	gl_Position = proj * gl_Position;\n"
			"	\n"
			"	out_col = vec4 ( 1, 1, 1, 1 ) * dot ( -lightDir, in_nor );"
			"}";
		vertexShader = glCreateShader ( GL_VERTEX_SHADER );
		GLint vertexShaderStringLength = strlen ( vertexShaderString );
		glShaderSource ( vertexShader, 1, &vertexShaderString, &vertexShaderStringLength );
		glCompileShader ( vertexShader );
		glGetShaderInfoLog ( vertexShader, 1024, &bufferLength, buffer );
		if ( bufferLength > 0 )
			PRPrintLog ( buffer );
		const GLchar * fragmentShaderString = "#version 330\n"
			"in vec4 out_col;"
			"void main () {\n"
			"	gl_FragColor = clamp ( out_col, 0, 1 );\n"
			"}";
		fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
		GLint fragmentShaderStringLength = strlen ( fragmentShaderString );
		glShaderSource ( fragmentShader, 1, &fragmentShaderString, &fragmentShaderStringLength );
		glCompileShader ( fragmentShader );
		glGetShaderInfoLog ( vertexShader, 1024, &bufferLength, buffer );
		if ( bufferLength > 0 )
			PRPrintLog ( buffer );

		program = glCreateProgram ();
		glAttachShader ( program, vertexShader );
		glAttachShader ( program, fragmentShader );
		glLinkProgram ( program );
		glGetProgramInfoLog ( program, 1024, &bufferLength, buffer );
		if ( bufferLength > 0 )
			PRPrintLog ( buffer );
		
		glGenVertexArrays ( 1, &vertexArrayObject );
		glBindVertexArray ( vertexArrayObject );

		PRModelGenerator * gen = new PRModelGenerator ( std::string ( "bunny.obj" ), PRModelTexCoord_ST );
		glGenBuffers ( 1, &vertexBufferObject );
		glBindBuffer ( GL_ARRAY_BUFFER, vertexBufferObject );

		glBufferData ( GL_ARRAY_BUFFER, gen->getDataSize (), gen->getData (), GL_STATIC_DRAW );

		glEnableVertexAttribArray ( glGetAttribLocation ( program, "in_pos" ) );
		glVertexAttribPointer ( glGetAttribLocation ( program, "in_pos" ), 3, GL_FLOAT, false, 40, 0 );
		int offset = sizeof ( float ) * 3;
		if ( gen->getProperties () & PRModelProperty_Normal )
		{
			glEnableVertexAttribArray ( glGetAttribLocation ( program, "in_nor" ) );
			glVertexAttribPointer ( glGetAttribLocation ( program, "in_nor" ), 3, GL_FLOAT, false, 40, ( void* ) offset );
			offset += sizeof ( float ) * 3;
		}
		if ( gen->getProperties () & PRModelProperty_TexCoord )
		{
			glEnableVertexAttribArray ( glGetAttribLocation ( program, "in_tex" ) );
			glVertexAttribPointer ( glGetAttribLocation ( program, "in_tex" ), 2, GL_FLOAT, false, 40, ( void* ) offset );
			offset += sizeof ( float ) * 2;
		}
		if ( gen->getProperties () & PRModelProperty_Diffuse )
		{
			glEnableVertexAttribArray ( glGetAttribLocation ( program, "in_col" ) );
			glVertexAttribPointer ( glGetAttribLocation ( program, "in_col" ), 4, GL_FLOAT, false, 40, ( void* ) offset );
			offset += sizeof ( float ) * 4;
		}

		glBindVertexArray ( 0 );

		vertexCount = gen->getDataSize () / offset;

		delete gen;
	}

	void onDestroy ()
	{
		glDeleteProgram ( program );
		glDeleteShader ( fragmentShader );
		glDeleteShader ( vertexShader );

		glDeleteVertexArrays ( 1, &vertexArrayObject );
		glDeleteBuffers ( 1, &vertexBufferObject );
	}

	void onDraw ( double dt )
	{
		GETGRAPHICSCONTEXT ( PRGraphicsContext_OpenGL );

		glClearColor ( 0, 0, 0, 1 );
		glClear ( GL_COLOR_BUFFER_BIT );

		glUseProgram ( program );
		PRMatrix world, temp;
		//PRVector3 scale ( 0.1f, 0.1f, 0.1f );
		//PRMatrix::createScale ( &scale, &world );
		static float rot = 0;
		rot += dt;
		PRMatrix::createRotationY ( rot, &temp );
		//PRMatrix::multiply ( &world, &temp, &world );
		glUniformMatrix4fv ( glGetUniformLocation ( program, "world" ), 1, false, ( GLfloat* ) &temp );

		PRMatrix view;
		PRMatrix::createLookAtRH ( &PRVector3 ( 5, 5, 5 ), &PRVector3 ( 0, 0, 0 ), &PRVector3 ( 0, 1, 0 ), &view );
		glUniformMatrix4fv ( glGetUniformLocation ( program, "view" ), 1, false, ( GLfloat* ) &view );

		PRMatrix proj;
		PRMatrix::createPerspectiveFieldOfViewRH ( PR_PIover4, 1280 / 720.f, 0.001f, 1000.0f, &proj );
		glUniformMatrix4fv ( glGetUniformLocation ( program, "proj" ), 1, false, ( GLfloat* ) &proj );

		PRVector4 worldLightPosition ( 10, 10, 10, 1 );
		glUniform4f ( glGetUniformLocation ( program, "worldLightPosition" ),
			worldLightPosition.x, worldLightPosition.y, worldLightPosition.z, worldLightPosition.w );

		//glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );

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