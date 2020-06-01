#version 330 core

in vec3 normal;
in vec2 texCoords;

uniform sampler2D tex;

out vec4 out_Color;

void main()
{
	float shading = dot(normal, vec3(0.0, 0.0, -1.0));
	if(shading < 0.0)
		shading = 0.0;
	vec4 texColor = texture(tex, texCoords);
	out_Color = vec4(texColor.xyz * shading, texColor.w);
}
