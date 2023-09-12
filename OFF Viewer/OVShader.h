#pragma once
#include "common.h"

class OVShader
{
private:
	const char* fileName;
	const char* source;
	GLuint id = 0;

public:
	OVShader(const char* fileName, int type);
	~OVShader();
	GLuint getId();
};