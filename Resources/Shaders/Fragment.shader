#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_TexSlot;

void main() {
	vec4 texColor = texture(u_TexSlot, v_TexCoord);
	color = texColor;
}
