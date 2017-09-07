#version 430

in vec3 v2fcolor;
out vec4 pixelcolor;

void main()
{
	pixelcolor = vec4(v2fcolor, 1.0);
}
