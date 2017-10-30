#include "Renderer.h"
#include "GL\glew.h"

Renderer* Renderer::renderer = new Renderer();

void Renderer::ExecutePass(Pass* pass)
{
	glUseProgram(pass->getObject()->getShaderInfo()->getProgramID());
	glBindVertexArray(pass->getObject()->getObjectID());
	glDrawElements(GL_TRIANGLES, pass->getObject()->getGeometry().numIndices, GL_UNSIGNED_SHORT, (void*)pass->getObject()->getIndicesBufferOffset());
}

void Renderer::init()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

Pass * Renderer::AddPass()
{
	Pass* pass = new Pass();
	PassArray.push_back(pass);
	return pass;
}
