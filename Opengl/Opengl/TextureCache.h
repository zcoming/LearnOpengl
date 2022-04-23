#pragma once
#include<glad/glad.h>
#include<FreeImage/FreeImage.h>
#include<map>
struct Texture
{
	Texture() : file(nullptr), texId(0) {}
	Texture(const GLchar* _file, GLuint _texId) : file(_file), texId(_texId) {}
	const GLchar* file;
	GLuint texId;
};

class TextureCache
{
public:
	static TextureCache* Ins() 
	{
		if (s_ins == NULL)
		{
			s_ins = new TextureCache();
		}
		return s_ins;
	}
	virtual ~TextureCache();

	GLuint LoadTexture(const GLchar* file);
	GLboolean AddImage(const GLchar* file, GLuint& texId);
	static void ErrorMsg(FREE_IMAGE_FORMAT fif, const char* msg);

private:
	TextureCache();
	static TextureCache* s_ins;
	std::map<const GLchar*, Texture> m_loaded;
};

