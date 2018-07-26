#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uvCoords;
layout(location = 2) in mat4 model;

out vec2 v_TexCoord;;

uniform mat4 u_View;
uniform mat4 u_Projection;


void main() {
	mat4 mvp = u_Projection * u_View * model;
	vec4 pos = mvp * position;
	gl_Position = pos;
	v_TexCoord = uvCoords;
}
