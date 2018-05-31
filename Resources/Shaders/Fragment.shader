#version 330 core

layout(location = 0) out vec4 color;

in vec4 fragColor;
in vec2 texCoord;

uniform sampler2D texSlot;
uniform vec3 lightColor;

void main() {
	//vec4 texColor = texture(texSlot, texCoord);
	float ambientStrength = 0.4f;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = ambient * fragColor.xyz;
	color = fragColor;
}
