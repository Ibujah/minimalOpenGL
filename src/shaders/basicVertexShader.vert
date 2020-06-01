#version 330 core

layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec3 Normal;

uniform mat4 pose;
uniform mat4 proj;

out vec3 normal;

void main()
{
	gl_Position =  proj * pose * vec4(Vertex.xyz, 1.0);

	normal = (pose * vec4(Normal.xyz, 0.0)).xyz;
}
