#include "OVModel.h"
#include "OVOption.h"
#include <vector>

OVModel::OVModel(const char* fileName, OVShaderProg* shaderProg)
{
	this->shaderProg = shaderProg;
	FILE* fp = fopen(fileName, "r");
	if (fp == nullptr)
	{
		fprintf(stderr, "file error: cannot open \"%s\"\n", fileName);
		exit(-1);
	}

	char buf[1024];
	int faceTmp;

	fgets(buf, sizeof(buf), fp);
	fgets(buf, sizeof(buf), fp);
	sscanf(buf, "%d %d", &vert, &faceTmp);

	vertArr = new vec4[vert];
	normalArr = new vec4[vert];
	std::vector<GLuint>* indexTmp = new vector<GLuint>[faceTmp];

	// vert
	for (int i = 0; i < vert; i++)
	{
		fgets(buf, sizeof(buf), fp);
		if (sscanf(buf, "%f %f %f", &vertArr[i].x, &vertArr[i].y, &vertArr[i].z) != 3)
		{
			i--;
			continue;
		}
		vertArr[i].w = 1.0f;
		normalArr[i] = vec4(0, 0, 0, 0);

		if (i == 0)
		{
			maxPos = vec3(vertArr[i].x, vertArr[i].y, vertArr[i].z);
			minPos = vec3(vertArr[i].x, vertArr[i].y, vertArr[i].z);
		}
		else
		{
			maxPos.x = std::max(maxPos.x, vertArr[i].x);
			maxPos.y = std::max(maxPos.y, vertArr[i].y);
			maxPos.z = std::max(maxPos.z, vertArr[i].z);
			minPos.x = std::min(minPos.x, vertArr[i].x);
			minPos.y = std::min(minPos.y, vertArr[i].y);
			minPos.z = std::min(minPos.z, vertArr[i].z);
		}
	}

	// face
	face = 0;
	for (GLuint i = 0; i < faceTmp; i++)
	{
		GLuint cnt, i1, i2, i0;
		fgets(buf, sizeof(buf), fp);

		if (sscanf(buf, "%u %u %u %u", &cnt, &i0, &i1, &i2) != 4)
		{
			i--;
			continue;
		}

		char* ptr = strtok(buf, " ");
		sscanf(ptr, "%u", &cnt);
		face += cnt - 2;

		for (int j = 0; j < cnt; j++)
		{
			ptr = strtok(nullptr, " ");
			sscanf(ptr, "%u", &i0);
			indexTmp[i].push_back(i0);
		}
	}
	indexArr = new GLuint[3 * face];
	
	for (GLuint i = 0, k = 0; i < faceTmp; i++)
	{
		int i0 = indexTmp[i][0];
		for (int j = 1; j < indexTmp[i].size() - 1; j++, k += 3)
		{
			int i1 = indexTmp[i][j];
			int i2 = indexTmp[i][j + 1];

			indexArr[k] = i0;
			indexArr[k + 1] = i1;
			indexArr[k + 2] = i2;

			vec3 a = vertArr[i0] - vertArr[i1];
			vec3 b = vertArr[i1] - vertArr[i2];
			vec3 normal3 = cross(a, b);
			vec4 normal = vec4(normal3.x, normal3.y, normal3.z, 0);
			if (OVOption::getInstance()->getNormal() == 1)
				normal *= -1;
			normalArr[i0] += normal;
			normalArr[i1] += normal;
			normalArr[i2] += normal;
		}
	}
	delete[] indexTmp;

	for (int i = 0; i < vert; i++)
		normalArr[i] = normalize(normalArr[i]);

	glGenBuffers(2, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 8 * vert * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * vert * sizeof(GLfloat), value_ptr(vertArr[0]));
	glBufferSubData(GL_ARRAY_BUFFER, 4 * vert * sizeof(GLfloat), 4 * vert * sizeof(GLfloat), value_ptr(normalArr[0]));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * face * sizeof(GLuint), indexArr, GL_STATIC_DRAW);

	fclose(fp);
}

OVModel::~OVModel()
{
	delete vertArr;
	delete indexArr;
	delete normalArr;
}

vec3 OVModel::getMaxPos()
{
	return maxPos;
}

vec3 OVModel::getMinPos()
{
	return minPos;
}

void OVModel::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	GLuint locPos = glGetAttribLocation(shaderProg->getId(), "aPos");
	GLuint locNormal = glGetAttribLocation(shaderProg->getId(), "aNormal");
	glEnableVertexAttribArray(locPos);
	glEnableVertexAttribArray(locNormal);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(locNormal, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(4 * vert * sizeof(GLfloat)));

	if (OVOption::getInstance()->getRender() == 0)
		glDrawElements(GL_POINTS, face * 3, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, face * 3, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();
}

float OVModel::getDist()
{
	vec3 center = (minPos + maxPos) * 0.5f;

	float dist = 0;
	for (int i = 0; i < vert; i++)
	{
		float x = vertArr[i].x - center.x;
		float y = vertArr[i].y - center.y;
		float z = vertArr[i].z - center.z;

		float coef = 4.5f;
		if (i == 0)
			dist = coef * abs(x) - z;
		else
			dist = std::max(dist, coef * abs(x) - z);
		dist = std::max(dist, coef * abs(y) - z);
	}

	return dist;
}