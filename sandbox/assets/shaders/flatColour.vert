#version 440 core
			
layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexColour;

out vec3 fragmentColour;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	fragmentColour = a_vertexColour;
	gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1);
}