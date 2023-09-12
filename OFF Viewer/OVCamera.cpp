#include "OVCamera.h"
#include "OVOption.h"

OVCamera::OVCamera(OVModel* ovModel, OVShaderProg* shaderProg)
{
	this->shaderProg = shaderProg;

	vec3 minPos = ovModel->getMinPos();
	vec3 maxPos = ovModel->getMaxPos();
	vec3 center = (minPos + maxPos) * 0.5f;
	float dist = ovModel->getDist();

	modelT = translate(mat4(1.0f), -center);
	modelR = mat4(1.0f);
	view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -dist));
	proj = perspectiveRH(((GLfloat)M_PI / 180.0f) * 30.0f, 1.0f, 0.1f, 2 * (maxPos.z + ovModel->getDist()));

	updateMat();
}

void OVCamera::updateMat()
{
	GLuint uModelT = glGetUniformLocation(shaderProg->getId(), "uModelT");
	GLuint uModelR = glGetUniformLocation(shaderProg->getId(), "uModelR");
	GLuint uView = glGetUniformLocation(shaderProg->getId(), "uView");
	GLuint uProj = glGetUniformLocation(shaderProg->getId(), "uProj");
	GLuint light = glGetUniformLocation(shaderProg->getId(), "light");

	glUniformMatrix4fv(uModelT, 1, GL_FALSE, value_ptr(modelT));
	glUniformMatrix4fv(uModelR, 1, GL_FALSE, value_ptr(modelR));
	glUniformMatrix4fv(uView, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(uProj, 1, GL_FALSE, value_ptr(proj));
	glUniform1i(light, OVOption::getInstance()->getLight());
}

void OVCamera::rotateModel(quat q)
{
	modelR = toMat4(q) * modelR;
	updateMat();
}