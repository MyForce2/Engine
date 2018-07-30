#version 400 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_FragmentPosition;

uniform sampler2D u_TexSlot;
uniform vec3 u_Color;



uniform vec3 u_ViewingPosition;
uniform vec4 u_AmbientLight;
uniform vec3 u_LightPosition;
const float specularStrength = 0.5f;


void main() {
	vec3 ambient = vec3(u_AmbientLight) * u_AmbientLight.a;

	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseLight = diffuseIntensity * vec3(u_AmbientLight);

	vec3 viewDirection = normalize(u_ViewingPosition - v_FragmentPosition);
	vec3 reflectDir = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * vec3(u_AmbientLight);

	color = vec4((ambient + diffuseLight + specular) * u_Color, 1.0);
}
