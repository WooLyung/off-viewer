#pragma once
#include "common.h"
#include "OVModel.h"
#include "OVShaderProg.h"

class OVCamera
{
private:
	OVShaderProg* shaderProg;
	mat4 modelT = mat4(1.0f);
	mat4 modelR = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);

public:
	OVCamera(OVModel* ovModel, OVShaderProg* shaderProg);
	void updateMat();
	void rotateModel(quat q);
};