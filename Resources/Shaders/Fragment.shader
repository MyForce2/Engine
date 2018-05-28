#version 330 core

layout(location = 0) out vec4 color;

in vec4 fragColor;
in vec2 texCoord;

uniform sampler2D texSlot;

void main() {
	color = texture(texSlot, texCoord);
	//color = fragColor;
}
