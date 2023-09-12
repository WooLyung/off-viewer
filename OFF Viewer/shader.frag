#version 330 core

in vec4 vNormal;
flat in int vLight;
out vec4 FragColor;

void main()
{
	if (vLight == 0)
	{
		FragColor = vec4(1, 1, 1, 1);
	}
	else if (vLight == 1)
	{
		vec3 normal = vNormal.xyz;
		float l1 = max(0, dot(normal, vec3(0, 0, 1)));
		FragColor.rgba = vec4(l1, l1, l1, 1.0);
	}
	else if (vLight == 2)
	{
		vec3 normal = vNormal.xyz;
		float l1 = max(0, dot(normal, vec3(-0.707, 0, 0.707)));
		float l2 = max(0, dot(normal, vec3(0.707, 0, 0.707)));
		FragColor.rgb = vec3(0.2, 1, 0.2) * l1 + vec3(0.2, 0.2, 1) * l2;
		FragColor.a = 1;
	}
}