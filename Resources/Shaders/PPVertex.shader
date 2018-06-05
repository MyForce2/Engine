#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uvCoord;

out vec2 v_UVCoord;

void main() {
	gl_Position = position;
	v_UVCoord = uvCoord;
}