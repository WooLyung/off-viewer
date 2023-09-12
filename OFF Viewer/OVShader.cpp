#include "OVShader.h"

OVShader::OVShader(const char* fileName, int type)
{
	this->fileName = fileName;
	source = loadFile(fileName);

	char buf[1024];
	GLint status;

	id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(id, sizeof(buf), nullptr, buf);
		printf("shader log: %s\n", buf);
		exit(-1);
	}
}

OVShader::~OVShader()
{
	delete source;
}

GLuint OVShader::getId()
{
	return id;
}