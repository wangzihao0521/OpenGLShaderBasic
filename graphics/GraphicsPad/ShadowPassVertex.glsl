#version 430

in layout(location = 0) vec3 Position;
in layout(location = 1) vec3 Color;
in layout(location = 2) vec3 normal;
in layout(location = 3) vec2 uv;
in layout(location = 4) vec4 tengent;

out vec2 f_uv;
out vec3 WorldPos;

uniform mat4 Zihao_MVP;
uniform mat4 Zihao_M2W;

void main()
{
	gl_Position = Zihao_MVP * vec4(Position, 1.0);
	f_uv = uv;
	WorldPos = vec3 (Zihao_M2W * vec4(Position,1));
}
