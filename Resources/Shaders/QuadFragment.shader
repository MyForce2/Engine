#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_UV;
in float v_SamplerID;

uniform sampler2D u_TexSlots[10];

void main() {
	vec3 textColor = vec3(0.5, 0.8f, 0.2);
	int i = int(v_SamplerID + 0.1);
	vec4 tex = texture(u_TexSlots[i], v_UV);
	if (i == 0) {
		if (tex.rgb == 0.f)
			discard;
		tex = vec4(vec3(tex) * textColor, 1.0);
	}
	color = tex;
}
