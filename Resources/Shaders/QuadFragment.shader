#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_UV;

uniform sampler2D u_TexSlot;

void main() {
	//vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_TexSlot, v_UV).r);
	vec3 textColor = vec3(0.5, 0.8f, 0.2);
	//color = vec4(textColor, 1.0) * sampled;
	vec4 t = texture(u_TexSlot, v_UV);
	if (t.r != 0.0)
		color = t * vec4(textColor, 1.0);
	else
		color = t;
}
