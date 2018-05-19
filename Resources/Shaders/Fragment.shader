#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_TextureSlot;

void main() {
	vec4 texColor = texture(u_TextureSlot, v_TexCoord);
	color = vec4(0.8, 0.6, 0.4, 1.0);
	color = texColor;
}
