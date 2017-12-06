#include "Renderer.h"
#include "GL\glew.h"
#include "PointLight.h"

Renderer* Renderer::renderer = new Renderer();

Camera Renderer::CurrentCamera = Camera();
Object* Renderer::P_light_obj = nullptr;
PointLight* Renderer::CurrentPointLight = nullptr;
Object* Renderer::CurrentObject = nullptr;

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

void Renderer::PushTexture2Array(Texture * tex)
{
	TextureArray.push_back(tex);
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

void Renderer::init_Pointlight()
{
	Shapedata CubeGeometry = ShapeFactory::MakeCube();
	Mesh m = CompleteMeshWithGeo(CubeGeometry);
	Object* P = new Object("", m);
	P->Setscale(glm::vec3(0.2f, 0.2f, 0.2f));
	P->setType(Light);
	BindMaterial2Object("Zihao_DefaultMaterial", P);
	P_light_obj = P;
}

void Renderer::init_SkyBox()
{
	CreateCubeInScene("SkyBox");
	CreateMaterial("SkyBox_Material", "CubeMapVertexShader.glsl", "CubeMapFragmentShader.glsl");
	Add_Property_Material("SkyBox_Material", "CubeMap", M_Texture3D, "SkyBox");
	BindMaterial2Object("SkyBox_Material", "SkyBox");
	setScaleforObject(glm::vec3(50, 50, 50),"SkyBox");
	ToggleSkyboxforObject("SkyBox");
}

void Renderer::init_ShadowFrameBuffer()
{
	GLuint i = TextureArray.size();
	ShadowFrameBuffer.init(i,ScreenWidth,ScreenHeight);
	PushTexture2Array(ShadowFrameBuffer.ColorTexture);
	PushTexture2Array(ShadowFrameBuffer.DepthTexture);
	CreateMaterial("M_ShadowPass", "ShadowPassVertex.glsl", "ShadowPassFragment.glsl");
	Add_Property_Material("M_ShadowPass", "ShadowMap", M_Texture2D, ShadowFrameBuffer.DepthTexture->getName());
	Add_Property_Material("M_ShadowPass", "Main_Texture", M_Texture2D, "white");

}

void Renderer::Add_LightUniform(Pass* pass)
{
	GLint AmbientuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_AmbientLight");
	if (AmbientuniformLocation >= 0)
		glUniform3fv(AmbientuniformLocation, 1, &AmbientLightIntense[0]);
	if (CurrentPointLight)
	{
		GLint LightPosuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_LightPosition_WS");
		if (LightPosuniformLocation >= 0)
			glUniform3fv(LightPosuniformLocation, 1, &CurrentPointLight->getPosition()[0]);
	}
	GLint ViewPosuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_ViewPosition_WS");
	if (ViewPosuniformLocation >= 0)
		glUniform3fv(ViewPosuniformLocation, 1, &CurrentCamera.getPosition()[0]);
	GLint AttenuationuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_Attenuation");
	if (AttenuationuniformLocation >= 0)
		glUniform1f(AttenuationuniformLocation, CurrentPointLight->getAttenuation());
}

void Renderer::Add_AllMaterialProperty(Material* mat)
{
	mat->AddAllPropertyUniform();
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pass->getObject()->getMesh().indicesBufferID);
	Add_Zihao_MVP(pass);
	if (CurrentPointLight)
		Add_LightUniform(pass);
	Add_AllMaterialProperty(&pass->getObject()->getMaterial());
	glDrawElements(GL_TRIANGLES, pass->getObject()->getGeometry().numIndices, GL_UNSIGNED_SHORT, 0);
}

Texture* Renderer::FindTextureByName(char * TexName)
{
	bool IsFound = false;
	std::string F_name = TexName;
	F_name += ".png";
	for (auto iter = TextureArray.begin(); iter != TextureArray.end(); iter++)
	{
		if ((*iter)->getName() == TexName || (*iter)->getName() == F_name)
		{
			IsFound = true;
			return *iter;
		}
	}
	if (!IsFound)
		printf("Cannot Find the Texture");
	return nullptr;
}

Material Renderer::FindMaterialByName(char * MatName)
{
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MatName) {
			return *iter;
		}
	}
	printf("Cannot find Material");
	return NULL;
}

void Renderer::init(GLsizei width, GLsizei height)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	ScreenWidth = width;
	ScreenHeight = height;
	AmbientLightIntense = glm::vec3(0.2, 0.2, 0.2);
	glViewport(0, 0, width, height);

	//import default texture
	ImportTexture("white.png");
	ImportTexture("black.png");
	ImportTexture("Normal_map.png");
	Import3DTexture("SkyBox", "right.png", "left.png", "bottom.png", "top.png", "back.png", "front.png");

	//Every obj created in scene uses default material first
	CreateMaterial("Zihao_DefaultMaterial");
	Add_Property_Material("Zihao_DefaultMaterial","MyTexture",M_Texture2D,"white" );
	Add_Property_Material("Zihao_DefaultMaterial", "NormalMap", M_Texture2D,"Normal_map.png");

	//Every Point Light created in scene use the same default light material 
	CreateMaterial("Zihao_PLightDefaultMaterial","PLight_VertexShader.glsl","PLight_FragmentShader.glsl");

	//init skybox
	init_SkyBox();

	init_ShadowFrameBuffer();

	//editor Camera
	Camera MainCamera("MainCamera",glm::vec3(0,0,5));
	PushCameraInVector(MainCamera);
	setCurrentCamera("MainCamera");

	//point light object initialize
	init_Pointlight();
//	bindShader2Material("DefaultMaterial", "Test_Vertexshader.glsl", "Test_Fragmentshader.glsl"); //todo


}

void Renderer::setScreenSize(GLsizei width, GLsizei height)
{
	ScreenHeight = height;
	ScreenWidth = width;
}

void Renderer::RanderShadowMap()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ShadowFrameBuffer.id);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	if (CurrentPointLight == nullptr)
	{	
		castingShadow = false;
		return;
	}
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,ShadowFrameBuffer.ColorTexture->getTextureID(), 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowFrameBuffer.DepthTexture->getTextureID(), 0);
	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	assert(status == GL_FRAMEBUFFER_COMPLETE);
	LightCamera.setPosition(CurrentPointLight->getPosition());
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{		
		if ((*iter)->Is_CastShadow())
		{			
			Pass* p = new Pass(&LightCamera);
			p->setObject(*iter);
			ExecutePass(p);
			castingShadow = true;
			delete p;
		}
	}
}

void Renderer::RenderScene()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	for (auto iter = PassArray.begin(); iter != PassArray.end(); iter++)
	{
		ExecutePass(*iter);
	}
	if (castingShadow) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
		{
			if ((*iter)->Is_ReceiveShadow() && (*iter)->getName()!= "SkyBox")
			{
				Material mat = FindMaterialByName("M_ShadowPass");
				Object obj = **iter;
				obj.bindMaterial(mat);
				if ((*iter)->getMaterial().FindPropertyByName("MyTexture")->getTexture()->getName() != "white.png")
					Bind_Property_Material("M_ShadowPass", "Main_Texture", (*iter)->getMaterial().FindPropertyByName("MyTexture")->getTexture()->getName());
				Pass* p = new Pass(&CurrentCamera);
				p->setObject(&obj);
				ExecutePass(p);
				delete p;
			}
		}
		glDisable(GL_BLEND);
	}
}

void Renderer::CreateCubeInScene(char* CubeName)
{
	Shapedata CubeGeometry = ShapeFactory::MakeCube();
	Mesh m = CompleteMeshWithGeo(CubeGeometry);
	Object*  cube = new Object(CubeName,m);
	AddObject(cube);
	BindMaterial2Object("Zihao_DefaultMaterial",cube);
	Pass* p = AddPass();
	p->setObject(cube);
	CurrentObject = cube;

}

void Renderer::CreatePlaneInScene(char* PlaneName)
{
	Shapedata PlaneGeometry = ShapeFactory::MakePlane();
	Mesh m = CompleteMeshWithGeo(PlaneGeometry);
	Object*  Plane = new Object(PlaneName, m);
	AddObject(Plane);
	BindMaterial2Object("Zihao_DefaultMaterial", Plane);
	Pass* p = AddPass();
	p->setObject(Plane);
	CurrentObject = Plane;
}

void Renderer::CreatePointLight(char * LightName, glm::vec3 pos)
{
	PointLight* P_light = new PointLight();
	Object* obj_P_light = new Object(LightName, P_light_obj->getMesh(),P_light_obj->getTransform(),Light);
	obj_P_light->Setposition(pos);
	BindMaterial2Object("Zihao_PLightDefaultMaterial", obj_P_light);
	P_light->setObject(obj_P_light);
	Pass* p = AddPass();
	p->setObject(obj_P_light);
	CurrentPointLight = P_light;
	CurrentObject = obj_P_light;
}

void Renderer::ImportTexture(char * FileName)
{
	QImage texture = QGLWidget::convertToGLFormat(QImage(FileName, "PNG"));

	GLuint i = TextureArray.size();
	glActiveTexture(GL_TEXTURE0+i);

	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	Texture* Tex_obj = new Texture(FileName,i,TextureID);
	TextureArray.push_back(Tex_obj);
}

void Renderer::Import3DTexture(char * FileName, char* rightImage, char* leftImage, char* topImage, char* bottomImage, char* frontImage, char* backImage)
{
	char* TexFile[6] = {rightImage, leftImage, topImage, bottomImage, frontImage, backImage};
	GLuint id = TextureArray.size();
	glActiveTexture(GL_TEXTURE0 + id);
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
	for (int i = 0; i < 6; ++i) {
		QImage Texdata = QGLWidget::convertToGLFormat(QImage(TexFile[i], "PNG"));
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Texdata.width(), Texdata.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Texdata.bits());
	}
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	Texture* Tex_obj = new Texture(FileName, id, TextureID);
	TextureArray.push_back(Tex_obj);
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

void Renderer::setPositionforCurrentObject(glm::vec3 position)
{
	if (CurrentObject == nullptr)
		return;
	CurrentObject->Setposition(position);
}

void Renderer::setRotationforObject(glm::vec3 rotation, char * ObjName)
{
	bool IsFinded = false;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		if ((*iter)->getName() == ObjName)
		{
			IsFinded = true;
			(*iter)->Setrotation(rotation);
		}

	}
	if (!IsFinded)
	{
		printf("Cannot find the obj");
	}
}

void Renderer::setRotationforCurrentObject(glm::vec3 rotation)
{
	if (CurrentObject == nullptr)
		return;
	CurrentObject->Setrotation(rotation);
}

void Renderer::setScaleforObject(glm::vec3 scale, char * ObjName)
{
	bool IsFinded = false;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		if ((*iter)->getName() == ObjName)
		{
			IsFinded = true;
			(*iter)->Setscale(scale);
		}

	}
	if (!IsFinded)
	{
		printf("Cannot find the obj");
	}
}

void Renderer::setScaleforCurrentObject(glm::vec3 scale)
{
	if (CurrentObject == nullptr)
		return;
	CurrentObject->Setscale(scale);
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

void Renderer::BindMaterial2CurrentObject(char * MaterialName)
{
	if (CurrentObject == nullptr)
		return;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			CurrentObject->bindMaterial(*iter);
			return;
		}
	}
	printf("Cannot find Material");
	return;
}

void Renderer::BindMaterial2Object(char * MaterialName, char * objName)
{
	bool FoundObj = false;
	Object* obj = nullptr;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++) {
		if ((*iter)->getName() == objName) {
			obj = *iter;
			FoundObj = true;
		}
	}
	if (!FoundObj)
	{
		printf("Cannot find the Object");
		return;
	}
	BindMaterial2Object(MaterialName, obj);
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
	if (pass->getObject()->Is_SkyBox())
	{
		CameraMatrix[3][0] = 0.0;
		CameraMatrix[3][1] = 0.0;
		CameraMatrix[3][2] = 0.0;
	}
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)ScreenWidth / ScreenHeight), 0.3f, 100.0f);

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), pass->getObject()->getTransform().getPosition());
	glm::mat4 RotationMatrix =  glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().z, glm::vec3(0, 0, 1)) *
								glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().x, glm::vec3(1, 0, 0)) *
								glm::rotate(glm::mat4(), pass->getObject()->getTransform().getRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), pass->getObject()->getTransform().getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix * Zihao_M2W;

	glm::mat4 Zihao_Light_MatrixW2P = projectionMatrix * LightCamera.getWorldToViewMatrix();
	
	
	GLint M2WuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_M2W");
	if (M2WuniformLocation >= 0)
		glUniformMatrix4fv(M2WuniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	GLint MVPuniformLocation = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(),"Zihao_MVP");
	if(MVPuniformLocation>=0)
		glUniformMatrix4fv(MVPuniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	GLint LightW2P = glGetUniformLocation(pass->getObject()->getMaterial().getShaderInfo().getProgramID(), "Zihao_LightMatrix_W2P");
	if (LightW2P >= 0)
		glUniformMatrix4fv(LightW2P, 1, GL_FALSE, &Zihao_Light_MatrixW2P[0][0]);

}

void Renderer::Add_Property_Material(char * MaterialName, char * PropertyName, M_PropertyType PropertyType, char * DefaultValue)
{
	bool IsFound = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			if (iter->checkPropertyNoExist(PropertyName))
			{
				Texture* tex = FindTextureByName(DefaultValue);
				if (tex)
				{
					M_Property* p = new M_Property(PropertyName, PropertyType, tex);
					iter->AddProperty(p);
					return;
				}
				else
					return;
			}
		}
	}
	if (!IsFound)
		printf("Cannot find the Material.");
	return;
}

void Renderer::Add_Property_Material(char * MaterialName, char * PropertyName, M_PropertyType PropertyType, glm::vec2 DefaultValue)
{
	bool IsFound = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			if (iter->checkPropertyNoExist(PropertyName))
			{			
				M_Property* p = new M_Property(PropertyName, PropertyType, DefaultValue);
				iter->AddProperty(p);
				return;
			}
		}
	}
	if (!IsFound)
		printf("Cannot find the Material.");
	return;
}

void Renderer::Add_Property_Material(char * MaterialName, char * PropertyName, M_PropertyType PropertyType, glm::vec3 DefaultValue)
{
	bool IsFound = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			if (iter->checkPropertyNoExist(PropertyName))
			{
				M_Property* p = new M_Property(PropertyName, PropertyType, DefaultValue);
				iter->AddProperty(p);
				return;
			}
		}
	}
	if (!IsFound)
		printf("Cannot find the Material.");
	return;
}

void Renderer::Add_Property_Material(char * MaterialName, char * PropertyName, M_PropertyType PropertyType, float DefaultValue)
{
	bool IsFound = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			if (iter->checkPropertyNoExist(PropertyName))
			{
				M_Property* p = new M_Property(PropertyName, PropertyType, DefaultValue);
				iter->AddProperty(p);
				return;
			}
		}
	}
	if (!IsFound)
		printf("Cannot find the Material.");
	return;
}

void Renderer::Bind_Property_Material(char * MaterialName, char * PropertyName, char * TexName)
{
	bool IsFound = false;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++) {
		if (iter->getName() == MaterialName) {
			M_Property* p = iter->FindPropertyByName(PropertyName);
			Texture* tex = FindTextureByName(TexName);
			if (p && tex)
			{
				if (p->getType() != M_Texture2D)
				{
					printf("Type is wrong");
					return;
				}
				else
					p->setTexture(tex);
				return;
			}
			else
				return;
			
		}
	}
	if (!IsFound)
		printf("Cannot find the Material.");
	return;
}

void Renderer::Bind_Property_CurrentMaterial(char * PropertyName, char * TexName)
{
	if (CurrentObject == nullptr)
		return;
	 
	M_Property* p = CurrentObject->getMaterial().FindPropertyByName(PropertyName);
	Texture* tex = FindTextureByName(TexName);
	if (p && tex)
	{
		if (p->getType() != M_Texture2D)
		{
			printf("Type is wrong");
			return;
		}
		else
			p->setTexture(tex);
		return;
	}
	else
		return;	
}

void Renderer::ToggleSkyboxforObject(char * objName)
{
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++) {
		if ((*iter)->getName() == objName) {
			(*iter)->toggleSkyBox();
			return;
		}
	}
	printf("Cannot Find the Object");
	return;
}


