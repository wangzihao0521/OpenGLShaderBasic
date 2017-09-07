#version 430

in vec3 v2fcolor;
in vec3 AmbientLightColor;
in vec3 VertexNormal;
in vec3 WorldPosition;
out vec4 pixelcolor;

uniform vec3 LightPosition;

void main()
{
	vec3 lightVector = normalize(LightPosition - WorldPosition);
	float brightness = clamp(dot(lightVector, VertexNormal),0,1);
	pixelcolor = vec4(vec3(brightness,brightness,brightness)+AmbientLightColor, 1.0);
}
