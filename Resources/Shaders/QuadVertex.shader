#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 u_UV;

void main() {
	gl_Position = position;
	u_UV = uv;
}
