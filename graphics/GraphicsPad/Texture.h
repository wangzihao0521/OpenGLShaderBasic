#ifndef ZIHAO_TEXTURE
#define ZIHAO_TEXTURE


class Texture {
protected:
	char* name;
	GLuint BufferID;
	GLuint TextureID;
public:
	Texture(char* texName, GLuint bufferID, GLuint textureID) :
		name(texName), BufferID(bufferID), TextureID(textureID) {};

	char* getName() const { return name; }
	GLuint getBufferID() const { return BufferID; }
	GLuint getTextureID() { return TextureID; }
};


#endif 