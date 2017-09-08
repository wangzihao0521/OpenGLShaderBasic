#version 430

in vec3 v2fcolor;
in vec3 AmbientLightColor;
in vec3 VertexNormal;
in vec3 WorldPosition;
in vec2 f_uv;
out vec4 pixelcolor;

uniform vec3 LightPosition;
uniform vec3 ViewPosition;
uniform sampler2D MyTexture;

void main()
{
	vec4 texColor = texture(MyTexture,f_uv);

	vec3 lightVector = normalize(LightPosition - WorldPosition);
	float brightness = clamp(dot(lightVector, VertexNormal),0,1);
	vec4 diffuseLight = brightness * texColor;

	vec3 reflectionVec = reflect(-lightVector,VertexNormal);
	vec3 viewdirection = normalize(ViewPosition - WorldPosition);
	float specularIntensity = pow(clamp(dot(viewdirection, reflectionVec),0,1),50);
	vec3 specularlight = specularIntensity * texColor.xyz;

	vec3 AmbientLight = AmbientLightColor * texColor.xyz;

	pixelcolor = vec4(diffuseLight.xyz + AmbientLight + specularlight, 1.0);
	
}
