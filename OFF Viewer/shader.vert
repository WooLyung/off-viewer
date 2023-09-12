#version 330 core

in vec4 aPos;
in vec3 aNormal;

out vec4 vNormal;
flat out int vLight;

uniform int light;
uniform mat4 uModelT;
uniform mat4 uModelR;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	gl_Position = uProj * uView * uModelR * uModelT * aPos;
	vNormal = uModelR * vec4(aNormal, 1);
	vLight = light;
}