#ifndef __POLYRAM_OPENGL_H__
#define __POLYRAM_OPENGL_H__

#include "polyram.h"

GLuint PRCreateTexture2D ( GLint internalFormat, GLint format, GLenum type, GLint width, GLint height ) {
	GLuint ret;
	glGenTextures ( 1, &ret );
	glBindTexture ( GL_TEXTURE_2D, ret );
	glTexImage2D ( GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr );
	return ret;
}

GLuint PRCreateTexture2D ( std::string & filename ) {
	void * data;
	unsigned width, height;
	if ( !PRGetImageData ( filename, &data, &width, &height ) )
		return 0;

	GLuint ret;
	glGenTextures ( 1, &ret );
	glBindTexture ( GL_TEXTURE_2D, ret );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

	delete [] data;

	return ret;
}

bool PRLoadShader ( std::string & vertexShaderFilename, std::string & pixelShaderFilename,
	GLuint * vertexShader, GLuint * pixelShader ) {
	void * data;
	unsigned dataSize;

	PRGetRawData ( vertexShaderFilename, &data, &dataSize );

	*vertexShader = glCreateShader ( GL_VERTEX_SHADER );
	glShaderSource ( *vertexShader, 1, ( GLchar ** ) &data, ( GLint* ) &dataSize );
	glCompileShader ( *vertexShader );
	
	delete [] data;

	PRGetRawData ( pixelShaderFilename, &data, &dataSize );

	*pixelShader = glCreateShader ( GL_FRAGMENT_SHADER );
	glShaderSource ( *pixelShader, 1, ( GLchar ** ) &data, ( GLint* ) &dataSize );
	glCompileShader ( *pixelShader );

	delete [] data;

	return true;
}

#endif