#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texPos;

out vec2 v_TexCoord;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

void main() {
	mat4 mvp = u_Projection * u_View * u_Model;
	vec4 pos = mvp * position;
	gl_Position = pos;
	v_TexCoord = texPos;
}
