#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float samplerID;

out vec2 v_UV;
out float v_SamplerID;

uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * position;
	v_UV = uv;
	v_SamplerID = samplerID;
}
