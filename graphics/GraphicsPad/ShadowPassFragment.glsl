#version 430

in vec2 f_uv;
in vec3 WorldPos;

out vec4 shadowColor;

uniform sampler2D ShadowMap;
uniform mat4 Zihao_LightMatrix_W2P;
uniform vec3 Zihao_AmbientLight;
uniform sampler2D Main_Texture;

void main()
{
	vec4 LightclipPos = Zihao_LightMatrix_W2P * vec4(WorldPos, 1.0);
	vec2 shadowmap_uv = vec2(LightclipPos.x / LightclipPos.w,LightclipPos.y / LightclipPos.w) ;
	vec2 shadowmap_uv_fixed = shadowmap_uv * 0.5 + 0.5;
	vec4 shadowmapColor = texture (ShadowMap,shadowmap_uv_fixed);
	vec4 texColor = texture (Main_Texture,f_uv);
	float shadowed;
	if(shadowmap_uv_fixed.x >= 1 || shadowmap_uv_fixed.x <=0 || shadowmap_uv_fixed.y >= 1 || shadowmap_uv_fixed.y <=0)
		shadowed = 1;
	else
		shadowed = clamp((shadowmapColor.x - LightclipPos.z / LightclipPos.w ) * 100 ,0,1);
	if(shadowed == 0)
		shadowColor = vec4(Zihao_AmbientLight * texColor.xyz,1);
	else
		shadowColor = vec4(0,0,0,0);

	//shadowColor = vec4 (1,0,0,0.5);
}
