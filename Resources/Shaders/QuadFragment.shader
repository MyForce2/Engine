#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_UV;

uniform sampler2D u_TexSlot;

void main() {
	color = texture(u_TexSlot, v_UV);
}
