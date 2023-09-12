#include "OVWindow.h"
#include "OVOption.h"

static OVCamera* cam;

OVWindow::OVWindow(int width, int height)
{
	// glfw
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	window = glfwCreateWindow(OVOption::getInstance()->getSize(), OVOption::getInstance()->getSize(), "OFF Viewer", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseClick);
	glfwSetCursorPosCallback(window, mouseMove);

	// glew
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// shader
	shaderProg = new OVShaderProg("shader.vert", "shader.frag");

	// model and camera
	model = new OVModel(OVOption::getInstance()->getFileName(), shaderProg);
	cam = camera = new OVCamera(model, shaderProg);

	init();
	run();
}

OVWindow::~OVWindow()
{
	glfwTerminate();

	delete shaderProg;
	delete model;
	delete camera;
}

void OVWindow::init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0F, 1.0F);
	glClearDepthf(1.0F);

	if (OVOption::getInstance()->getRender() == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OVWindow::run()
{
	while (!glfwWindowShouldClose(window))
	{
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void OVWindow::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	model->draw();
	glFinish();
}

static vec3 preAxis = vec3(0, 0, 0);
static bool pressed = false;

void mouseClick(GLFWwindow* win, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		if (action == GLFW_PRESS)
			pressed = true;
		else if (action == GLFW_RELEASE)
			pressed = false;
	}
}

void mouseMove(GLFWwindow* win, double xscr, double yscr)
{
	float x = xscr / OVOption::getInstance()->getSize();
	float y = yscr / OVOption::getInstance()->getSize();

	vec2 v = vec2(x * 2 - 1, -y * 2 + 1);
	float r = sqrt(v.x * v.x + v.y * v.y);
	if (r > 1.0f)
	{
		r = 1.0f;
		v = normalize(v);
	}
	float z = sqrt(1 - r * r);

	vec3 axis = vec3(v.x, v.y, z);

	if (pressed)
		cam->rotateModel(rotation(preAxis, axis));

	preAxis = axis;
}