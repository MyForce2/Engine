#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texPos;

layout(std140) uniform camera_data {
	mat4 view;
	mat4 projection;
	mat4 model;
};

out vec2 v_TexCoord;



void main() {
	mat4 mvp = projection * view * model;
	vec4 pos = mvp * position;
	gl_Position = pos;
	v_TexCoord = texPos;
}
