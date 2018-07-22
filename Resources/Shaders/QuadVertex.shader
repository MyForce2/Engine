#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in int samplerID;
layout(location = 3) in int isText;
layout(location = 4) in vec3 textColor;

out vec2 v_UV;
out vec3 v_TextColor;
flat out int v_IsText;
flat out int v_SamplerID;


uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * position;
	v_UV = uv;
	v_TextColor = textColor;
	v_IsText = isText;
	v_SamplerID = samplerID;
}
