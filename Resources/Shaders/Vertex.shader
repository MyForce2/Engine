#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texPos;



out vec2 v_TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
	mat4 mvp = projection * view * model;
	vec4 pos = mvp * position;
	gl_Position = pos;
	v_TexCoord = texPos;
}
