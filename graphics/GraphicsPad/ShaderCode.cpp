const char* vertexshader =
""
"#version 430\r\n"
""
"in layout(location = 0) vec2 Position;"
"in layout(location = 1) vec3 Color;"
"out vec3 v2fcolor;"
""
"void main()"
"{"
"	gl_Position = vec4(Position, 0.0, 1.0);"
"	v2fcolor = Color;"
"}";

const char* fragmentshader =
""
"#version 430\r\n"
""
"in vec3 v2fcolor;"
"out vec4 pixelcolor;"
""
"void main()"
"{"
"	pixelcolor = vec4(v2fcolor, 1.0);"
"}";