#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

out vec2 TEX;

void main()
{
	gl_Position = project * view * model * vec4(pos, 1);
	TEX = tex;
}