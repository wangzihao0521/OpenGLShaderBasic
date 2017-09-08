#version 430

in layout(location = 0) vec3 Position;
in layout(location = 1) vec3 Color;
in layout(location = 2) vec3 normal;
in layout(location = 3) vec2 uv;
out vec3 v2fcolor;
out vec3 AmbientLightColor;
out vec3 VertexNormal;
out vec3 WorldPosition;
out vec2 f_uv;

uniform mat4 FullTransformMatrix;
uniform mat4 Model2WorldMatrix;
uniform vec3 AmbientLight;

void main()
{
	gl_Position = FullTransformMatrix * vec4(Position, 1.0);
	v2fcolor = Color;
	AmbientLightColor = AmbientLight;
	VertexNormal = vec3 (transpose(inverse(Model2WorldMatrix)) * vec4(normal,0));
	WorldPosition = vec3(Model2WorldMatrix * vec4(Position,1.0));
	f_uv = uv;
}