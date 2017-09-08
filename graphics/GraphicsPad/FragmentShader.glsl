#version 430

in vec3 v2fcolor;
in vec3 AmbientLightColor;
in vec3 VertexNormal;
in vec3 WorldPosition;
out vec4 pixelcolor;

uniform vec3 LightPosition;
uniform vec3 ViewPosition;

void main()
{
	vec3 lightVector = normalize(LightPosition - WorldPosition);
	float brightness = clamp(dot(lightVector, VertexNormal),0,1);

	vec3 reflectionVec = reflect(-lightVector,VertexNormal);
	vec3 viewdirection = normalize(ViewPosition - WorldPosition);
	float specularIntensity = pow(clamp(dot(viewdirection, reflectionVec),0,1),50);
	vec3 specularlight = specularIntensity * vec3(1.0,0.0,0.0);
	pixelcolor = vec4(vec3(brightness,brightness,brightness)+AmbientLightColor + specularlight, 1.0);
}
