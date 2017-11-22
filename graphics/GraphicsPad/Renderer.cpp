#include "Renderer.h"
#include "GL\glew.h"

Renderer* Renderer::renderer = new Renderer();

GLuint Renderer::bindandfillvertexbuffer(Shapedata geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, geometry.VertexBufferSize(), geometry.vertices, GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindandfillindicesbuffer(Shapedata geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.IndicesBufferSize(), geometry.Indices, GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindvertexarray(GLuint vbufferID, GLuint ibufferID)
{
	GLuint GeometryID;
	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER , vbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(11 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibufferID);

	return GeometryID;
}

void Renderer::PushCameraInVector(Camera cam)
{
	CameraArray.push_back(cam);
}

void Renderer::setCurrentCamera(char * camName)
{
	for (auto iter = CameraArray.begin(); iter != CameraArray.end(); ++iter)
	{
		if (iter->getName() == camName)
		{
			CurrentCamera = *iter;
		}
		else
		{
			printf("Cannot find target camera");
		}
	}
}

Object * Renderer::CreateObject(char* ObjName,Shapedata geometry)
{
	Object* obj = new Object(ObjName,geometry);
	return obj;
}

void Renderer::ExecutePass(Pass* pass)
{
	glUseProgram(pass->getObject()->getMaterial().getShaderInfo().getProgramID());
	glBindVertexArray(pass->getObject()->getObjectID());
	Add_Zihao_MVP(pass);
	glDrawElements(GL_TRIANGLES, pass->getObject()->getGeometry().numIndices, GL_UNSIGNED_SHORT, 0);
}

void Renderer::init(GLsizei width, GLsizei height)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	ScreenWidth = width;
	ScreenHeight = height;
	glViewport(0, 0, width, height);
	CreateMaterial("DefaultMaterial");
	Camera MainCamera;
	PushCameraInVector(MainCamera);
	setCurrentCamera("MainCamera");
//	bindShader2Material("DefaultMaterial", "Test_Vertexshader.glsl", "Test_Fragmentshader.glsl"); //todo


}

void Renderer::CreateCubeInScene(char* CubeName)
{
	Shapedata CubeGeometry = ShapeFactory::MakeCube();
//	if(!CheckGeometryExist(CubeGeometry))
	Mesh m = CompleteMeshWithGeo(CubeGeometry);
	Object*  cube = new Object(CubeName,m);
	AddObject(cube);
	BindMaterial2Object("DefaultMaterial",cube);
//	cube->Setposition(glm::vec3(0.0, 0.0, -5.0));
	Pass* p = AddPass();
	p->setObject(cube);


}

void Renderer::CreatePlaneInScene(char* PlaneName)
{
	Shapedata PlaneGeometry = ShapeFactory::MakePlane();
	//	if(!CheckGeometryExist(CubeGeometry))
	Mesh m = CompleteMeshWithGeo(PlaneGeometry);
	Object*  Plane = new Object(PlaneName, m);
	AddObject(Plane);
	BindMaterial2Object("DefaultMaterial", Plane);
	//	cube->Setposition(glm::vec3(0.0, 0.0, -5.0));
	Pass* p = AddPass();
	p->setObject(Plane);


}

void Renderer::setPositionforObject(glm::vec3 position, char * ObjName)
{
	bool IsFinded = false;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		if ((*iter)->getName() == ObjName)
		{	
			IsFinded = true;
			(*iter)->Setposition(position);
		}
	
	}
	if (!IsFinded)
	{
		printf("Cannot find the obj");
	}
}

void Renderer::BindShader2Material(char* VshaderFileName, char* FshaderFileName, Material& material)
{
	bool Compiled = material.CompileShader(VshaderFileName, FshaderFileName);
	if (Compiled) {
		material.setVertexShader(VshaderFileName);
		material.setFragmentShader(FshaderFileName);
	}
	
}

void Renderer::BindMaterial2Object(char* MaterialName, Object * obj)
{
	bool Binded = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			obj->bindMaterial(*iter);
			Binded = true;
		}
	}
	if (!Binded)
		printf("Cannot find Material");
	return;
	
}

Pass * Renderer::AddPass()
{
	Pass* pass = new Pass(&CurrentCamera);
	PassArray.push_back(pass);
	return pass;
}

Material Renderer::CreateMaterial(char * Materialname, char * VshaderFileName, char * FshaderFileName)
{
	Material material(Materialname, VshaderFileName, FshaderFileName);
	bool Compiled = material.CompileShader(VshaderFileName, FshaderFileName);
	if (Compiled) {
		MaterialArray.push_back(material);
		return material;
	}
	else
	{
		printf("Create Material failed");
		return NULL;
	}
}

Mesh Renderer::CompleteMeshWithGeo(Shapedata geometry)
{
	for (auto iter = MeshArray.begin(); iter != MeshArray.end(); iter++)
	{
		if (geometry == iter->geometry)
			return *iter;
	}
	Mesh m(geometry) ;
	m.VertexBufferID = bindandfillvertexbuffer(geometry);
	m.indicesBufferID = bindandfillindicesbuffer(geometry);
	m.GeometryID = bindvertexarray(m.VertexBufferID, m.indicesBufferID);
	AddMesh(m);
	return m;
}

void Renderer::AddMesh(Mesh mesh)
{
	MeshArray.push_back(mesh);
}

void Renderer::AddObject(Object* obj)
{
	ObjectArray.push_back(obj);
}

void Renderer::Add_Zihao_MVP(Pass* pass)
{
	glm::mat4 CameraMatrix = pass->getCamera()->getWorldToViewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)ScreenWidth / ScreenHeight), 0.3f, 100.0f);

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), pass->getObject()->getTransform().getPosition());
	glm::mat4 RotationMatrix =  glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().z, glm::vec3(0, 0, 1)) *
								glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().x, glm::vec3(1, 0, 0)) *
								glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), pass->getObject()->getTransform().getScale());
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix * TransformMatrix * RotationMatrix * ScaleMatrix;

	GLuint MVPuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(),"Zihao_MVP");
	glUniformMatrix4fv(MVPuniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);

}


