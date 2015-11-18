#version 330 core

in vec4 vPosition;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection*view*model*vPosition;
	color = vPosition
	;
}