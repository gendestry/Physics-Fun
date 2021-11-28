#version 330 core
layout (location = 0) in vec3 aVertexPos;

void main() {
	gl_Position = vec4(aVertexPos, 1.0);
}