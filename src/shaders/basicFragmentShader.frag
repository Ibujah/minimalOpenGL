#version 330 core

in vec3 normal;

out vec4 out_Color;

void main()
{
	float color = dot(normal, vec3(0.0, 0.0, -1.0));
	if(color < 0.0)
		color = 0.0;
	out_Color = vec4(color, color, color, 1.0);
}
