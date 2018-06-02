#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 v_Normal;
out vec3 v_FragPos;

void main() {
	v_FragPos = vec3(model * position);
	v_Normal = normal;
	gl_Position = projection * view * model * position;
}