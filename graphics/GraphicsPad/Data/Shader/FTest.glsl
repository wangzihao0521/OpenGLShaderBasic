#version 430

in vec3 VertexColor;
out vec4 pixelcolor;

uniform vec3 newColor;


void main()
{
	pixelcolor = vec4(newColor,1.0);
}
