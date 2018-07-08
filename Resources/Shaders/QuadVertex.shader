#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 v_UV;

uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * position;
	v_UV = uv;
}
