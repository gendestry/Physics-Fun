#version 330 core
layout (location = 0) out vec4 Color;

in vec3 vNormalPos;
in vec2 vTexCoord;

uniform vec4 imColor;

void main() {
	vec3 lightDir = normalize(vec3(1.2, 0.8, 1.0));
	float dif = max(0.1, dot(lightDir, vNormalPos));

	Color = vec4(imColor.xyz * dif, imColor.w);
}