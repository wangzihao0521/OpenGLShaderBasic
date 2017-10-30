#pragma once
#include <vector>
#include "Pass.h"

class Renderer {
protected:
	std::vector<Pass*> PassArray;
	static Renderer* renderer;
public:
	Renderer() {};

	void ExecutePass(Pass* pass);
	void init();
	Pass* AddPass();
	Renderer* getInstatnce() { return renderer; }
};
