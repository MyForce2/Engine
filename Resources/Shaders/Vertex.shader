#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in mat4 model;

out vec3 v_Normal;
out vec3 v_FragmentPosition;

uniform mat4 u_View;
uniform mat4 u_Projection;


void main() {
	mat4 mvp = u_Projection * u_View * model;
	vec4 pos = mvp * position;
	gl_Position = pos;
	v_Normal = normal;
	v_FragmentPosition = vec3(model * position);
}
