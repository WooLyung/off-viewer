#pragma once
#include "common.h"

class OVOption
{
private:
	static OVOption* instance;

	char fileName[1024];
	int size = 500;
	int render = 2; // point, edge, face
	int light = 1;

	OVOption() {};

public:
	static OVOption* getInstance();

	void readParams(int argc, const char* argv[]);
	const char* getFileName();
	int getSize();
	int getRender();
	int getLight();
};