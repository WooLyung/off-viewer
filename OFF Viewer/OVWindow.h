#pragma once
#include "common.h"
#include "OVShaderProg.h"
#include "OVModel.h"
#include "OVCamera.h"

class OVWindow
{
private:
	GLFWwindow* window;
	OVShaderProg* shaderProg;
	OVModel* model;
	OVCamera* camera;

	void init();
	void run();
	void draw();

public:
	OVWindow(int width, int height);
	~OVWindow();
};

void mouseClick(GLFWwindow* win, int button, int action, int mods);
void mouseMove(GLFWwindow* win, double xscr, double yscr);