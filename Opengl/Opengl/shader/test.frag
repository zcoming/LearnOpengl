#version 330 core
in vec2 TEX;

uniform sampler2D mainTexture;

out vec4 color;

void main()
{
	color = texture(mainTexture, TEX);
}