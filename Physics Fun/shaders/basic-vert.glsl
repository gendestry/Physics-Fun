#version 330 core
layout (location = 0) in vec3 aVertexPos;
layout (location = 1) in vec3 aNormalPos;
layout (location = 2) in vec2 aTexCoord;

out vec3 vNormalPos;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	vNormalPos = normalize(vec3(transpose(inverse(model)) * vec4(aNormalPos, 1.0)));
	vTexCoord = aTexCoord;
	gl_Position = proj * view * model * vec4(aVertexPos, 1.0);
}