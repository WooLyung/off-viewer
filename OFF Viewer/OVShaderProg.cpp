#include "OVShaderProg.h"

OVShaderProg::OVShaderProg(const char* vertName, const char* fragName)
{
	vert = new OVShader(vertName, GL_VERTEX_SHADER);
	frag = new OVShader(fragName, GL_FRAGMENT_SHADER);

	char buf[1024];
	GLint status;

	id = glCreateProgram();
	glAttachShader(id, vert->getId());
	glAttachShader(id, frag->getId());
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);

	if (status == false)
	{
		glGetProgramInfoLog(id, sizeof(buf), nullptr, buf);
		printf("link log: %s\n", buf);
		exit(-1);
	}

	glValidateProgram(id);
	glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
	if (status == false)
	{
		glGetProgramInfoLog(id, sizeof(buf), nullptr, buf);
		printf("validate log: %s\n", buf);
	}

	glUseProgram(id);
}

OVShaderProg::~OVShaderProg()
{
	delete vert;
	delete frag;
}

GLuint OVShaderProg::getId()
{
	return id;
}