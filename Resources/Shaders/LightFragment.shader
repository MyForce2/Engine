#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main() {
	vec3 objColor = vec3(1.0f, 127.f / 256.f, 80.f / 256.f);
	float ambientStrength = 0.1f;
	vec3 ambient = ambientColor * ambientStrength;
	vec3 norm = normalize(v_Normal);
	vec3 lightDirection = normalize(lightPos - v_FragPos);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient * diffuse) * objColor;
	color = vec4(result, 1.0);
}