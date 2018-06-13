#version 330 core

layout(location = 0) out vec4 outColor;

#define M_PI 3.1415926535897932384626433832795

in vec2 v_UVCoord;

uniform sampler2D u_TextureSlot;
uniform vec3 u_ClearColor;

void main() {


	const float pixelOffset = 1.0 / 10000.0;

	if (vec3(texture(u_TextureSlot, v_UVCoord)) == u_ClearColor) {
		outColor = vec4(u_ClearColor, 1.0);
		return;
	}

	vec2 offsets[9] = vec2[](
		vec2(-pixelOffset, pixelOffset), // top-left
		vec2(0.0f, pixelOffset), // top-center
		vec2(pixelOffset, pixelOffset), // top-right
		vec2(-pixelOffset, 0.0f),   // center-left
		vec2(0.0f, 0.0f),   // center-center
		vec2(pixelOffset, 0.0f),   // center-right
		vec2(-pixelOffset, -pixelOffset), // bottom-left
		vec2(0.0f, -pixelOffset), // bottom-center
		vec2(pixelOffset, -pixelOffset)  // bottom-right    
	);

	// The value 3x3 matrix for the kernel effect , this effect is edge detection
	float kernel[9] = float[](
		1, 1, 1,
		1, -8, 1,
		1, 1, 1
	);


	vec3 processedTex[9];
	for (int i = 0; i < 9; i++)
	{
		processedTex[i] = vec3(texture(u_TextureSlot, v_UVCoord.xy + offsets[i]));
	}
	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++)
		col += processedTex[i] * kernel[i];

	//col.r = 0.f;
	//col.g = 0.f;
	outColor = vec4(col, 1.0);
	outColor = texture(u_TextureSlot, v_UVCoord);
}