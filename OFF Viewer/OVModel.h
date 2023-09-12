#pragma once
#include "common.h"
#include "OVShaderProg.h"

class OVModel
{
private:
	OVShaderProg* shaderProg;
	vec4* vertArr;
	vec4* normalArr;
	GLuint* indexArr;

	vec3 maxPos, minPos;
	int vert, face;

	GLuint buffer[2];

public:
	OVModel(const char* fileName, OVShaderProg* shaderProg);
	~OVModel();
	
	void draw();
	vec3 getMaxPos();
	vec3 getMinPos();
	float getDist();
};