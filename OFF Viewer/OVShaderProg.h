#pragma once
#include "common.h"
#include "OVShader.h"

class OVShaderProg
{
private:
	OVShader* vert;
	OVShader* frag;
	GLuint id = 0;

public:
	OVShaderProg(const char* vertName, const char* fragName);
	~OVShaderProg();
	GLuint getId();
};