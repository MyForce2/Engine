#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uvCoords;
layout(location = 2) in vec4 color;
layout(location = 3) in mat4 translation;

out vec4 fragColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
	mat4 mvp = projection * view * translation;
	vec4 pos = mvp * position;
	gl_Position = pos;
	fragColor = color;
	texCoord = uvCoords;
}
