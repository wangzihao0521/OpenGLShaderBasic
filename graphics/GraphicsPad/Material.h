#pragma once

class Material {
protected:
	char* VshaderFileName;
	char* FshaderFileName;

public:
	Material(char* Vshaderfilename = nullptr, char* Fshaderfilename = nullptr) :
		VshaderFileName(Vshaderfilename), FshaderFileName(Fshaderfilename) {};

};
