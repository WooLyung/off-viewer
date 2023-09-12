#include "common.h"
#include "OVWindow.h"
#include "OVOption.h"

int main(int argc, const char* argv[])
{
	OVOption::getInstance()->readParams(argc, argv);
	OVWindow* window = new OVWindow(1000, 1000);
	delete window;
}