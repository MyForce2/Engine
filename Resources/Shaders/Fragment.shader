#version 330 core

layout(location = 0) out vec4 color;

in vec4 fragColor;

void main() {
	color = fragColor;
	//color = vec4(0.1, 0.5, 0.5, 1.0);
}
