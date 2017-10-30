#pragma once

class ShaderInfo {
protected:
	GLuint programID;
public:
	ShaderInfo():
		programID(0){}

	GLuint getProgramID() const { return programID; }
};
