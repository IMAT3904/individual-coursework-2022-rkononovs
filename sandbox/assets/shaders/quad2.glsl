#region Vertex

#version 440 core

layout(location = 0) in vec4 a_vertexPosition;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in int a_texUnit;

out vec2 texCoord;
out flat int texUnit;

layout (std140) uniform b_cameraQuad
{
	mat4 u_projection;
	mat4 u_view;
};

void main()
{
	texCoord = vec2(a_texCoord);
	texUnit = a_texUnit;
	gl_Position = u_projection * u_view * a_vertexPosition;
}

#region Fragment

#version 440 core
			
layout(location = 0) out vec4 colour;

in vec2 texCoord;
in flat int texUnit;

uniform vec4 u_tint;
uniform sampler2D[32] u_texData;

void main()
{	
	colour = texture(u_texData[texUnit], texCoord) * u_tint;
}