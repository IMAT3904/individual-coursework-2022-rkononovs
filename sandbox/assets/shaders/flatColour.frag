#version 440 core
			
layout(location = 0) out vec4 colour;

in vec3 fragmentColour;

void main()
{
	colour = vec4(fragmentColour, 1.0);
}