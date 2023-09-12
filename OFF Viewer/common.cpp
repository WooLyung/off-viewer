#include "common.h"

const char* loadFile(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "file error: cannot open \"%s\"\n", filename);
		exit(-1);
	}

	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
	rewind(fp);
	char* buf = (char*)malloc(sizeof(char) * (len + 4));

	size_t size = fread(buf, sizeof(char), len, fp);
	fclose(fp);
	buf[size] = '\0';

	return (const char*)buf;
}