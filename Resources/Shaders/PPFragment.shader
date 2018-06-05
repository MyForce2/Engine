#version 330 core

layout(location = 0) out vec4 outColor;

#define M_PI 3.1415926535897932384626433832795

in vec2 v_UVCoord;

uniform sampler2D u_TextureSlot;

void main() {
	vec4 texColor = texture(u_TextureSlot, v_UVCoord);
	texColor.y = sin(texColor.y);
	outColor = texColor;
}