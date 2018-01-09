#version 430

in vec3 VertexColor;
in vec3 VertexPosition;
in vec3 vertexnormal;
in vec2 f_uv;
in mat4 TengentToModelTransform;
out vec4 pixelcolor;

uniform vec3 Zihao_LightPosition_WS;
uniform vec3 Zihao_AmbientLight;
uniform mat4 Zihao_M2W;
uniform vec3 Zihao_ViewPosition_WS;
uniform float Zihao_Attenuation;
uniform sampler2D MyTexture;
uniform sampler2D NormalMap;


void main()
{
	vec4 texColor = texture(MyTexture,f_uv);
	vec3 AmbientLight = Zihao_AmbientLight * texColor.xyz;

	vec4 normalmapcolor = texture(NormalMap,f_uv);
	vec3 FixedNormalVector = (normalmapcolor.xyz - vec3(0.5f,0.5f,0.5f))*2;
	vec3 ModelNormal = vec3(TengentToModelTransform * vec4(FixedNormalVector,0.0));

	vec3 WorldPosition = vec3(Zihao_M2W * vec4(VertexPosition,1.0));
	vec3 LightVector = normalize(Zihao_LightPosition_WS - WorldPosition);
	float distance = length(Zihao_LightPosition_WS - WorldPosition);
	float attenuation = mix(0,1 / (Zihao_Attenuation * pow(distance,2)),Zihao_Attenuation * 100);

	vec3 PreWorldNormal = vec3 (transpose(inverse(Zihao_M2W)) * vec4(vertexnormal,0));
	vec3 ActualModelNormal = mix(vertexnormal,ModelNormal,clamp(dot(LightVector, PreWorldNormal)*10000,0,1));
	vec3 WorldNormal = vec3 (transpose(inverse(Zihao_M2W)) * vec4(ActualModelNormal,0));

//	vec3 WorldNormal = vec3 (transpose(inverse(Zihao_M2W)) * vec4(vertexnormal,0));
	float brightness = clamp(dot(LightVector, WorldNormal),0,1);
	vec3 DiffuseLight = attenuation * vec3(brightness,brightness,brightness) * vec3(texColor);

	vec3 reflectionVec = reflect(-LightVector,WorldNormal);
	vec3 viewdirection = normalize(Zihao_ViewPosition_WS - WorldPosition);
	float specularIntensity =  pow(clamp(dot(viewdirection, reflectionVec),0,1),50);
	vec3 SpecularLight = attenuation * specularIntensity * vec3(1.0,0.0,0.0);

	pixelcolor = vec4(AmbientLight + DiffuseLight + clamp(SpecularLight,0,1),1.0);
//	pixelcolor = vec4(WorldNormal,1);
//	pixelcolor = normalmapcolor;
}
