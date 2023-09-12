#include <cstring>
#include "OVOption.h"

OVOption* OVOption::instance = nullptr;

OVOption* OVOption::getInstance()
{
	if (instance == nullptr)
		instance = new OVOption();
	return instance;
}

void OVOption::readParams(int argc, const char* argv[])
{
	const char* msg = "usage: cmd [-f fileName] [-s size] [-r {p|e|f}] [-l {0|1|2}]\n";
	bool name = false;

	for (int i = 1; i < argc; i++)
	{
		if (i == argc - 1)
		{
			printf(msg);
			exit(0);
		}

		if (strcmp(argv[i], "-f") == 0)
		{
			strcpy(fileName, argv[++i]);
			name = true;
		}
		else if (strcmp(argv[i], "-s") == 0)
		{
			try
			{
				sscanf(argv[++i], "%d", &size);
			}
			catch (exception e)
			{
				printf(msg);
				exit(0);
			}
		}
		else if (strcmp(argv[i], "-r") == 0)
		{
			i++;
			if (strcmp(argv[i], "p") == 0)
				render = 0;
			else if (strcmp(argv[i], "e") == 0)
				render = 1;
			else if (strcmp(argv[i], "f") == 0)
				render = 2;
			else
			{
				printf(msg);
				exit(0);
			}
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			i++;
			if (strcmp(argv[i], "0") == 0)
				light = 0;
			else if (strcmp(argv[i], "1") == 0)
				light = 1;
			else if (strcmp(argv[i], "2") == 0)
				light = 2;
			else
			{
				printf(msg);
				exit(0);
			}
		}
		else
		{
			printf(msg);
			exit(0);
		}
	}

	if (!name)
	{
		printf(msg);
		exit(0);
	}
}

const char* OVOption::getFileName()
{
	return fileName;
}

int OVOption::getSize()
{
	return size;
}

int OVOption::getRender()
{
	return render;
}

int OVOption::getLight()
{
	return light;
}