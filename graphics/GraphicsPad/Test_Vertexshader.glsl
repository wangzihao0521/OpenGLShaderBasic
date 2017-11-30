#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 Color;
in layout(location = 2) vec3 normal;
in layout(location = 3) vec2 uv;
in layout(location = 4) vec4 tengent;

out vec3 VertexColor;
out vec3 VertexPosition;
out vec3 vertexnormal;
out vec2 f_uv;
out mat4 TengentToModelTransform;

uniform mat4 Zihao_MVP;

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	VertexPosition = position;
	VertexColor = Color;
	vertexnormal = normal;
	f_uv = uv;
	vec3 BiotengentVector = normalize(cross(normal,vec3(tengent)) * tengent.w);
	TengentToModelTransform = mat4(vec4(vec3(tengent),0.0),vec4(BiotengentVector,0.0),vec4(normal,0.0),vec4(position,1.0));
}

