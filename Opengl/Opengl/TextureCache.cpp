#include "TextureCache.h"
#include<iostream>

TextureCache* TextureCache::s_ins = nullptr;

TextureCache::TextureCache()
{
	FreeImage_Initialise(false);
	FreeImage_SetOutputMessage(TextureCache::ErrorMsg);
}

TextureCache::~TextureCache()
{
	FreeImage_DeInitialise();
	for (auto it = m_loaded.begin(); it != m_loaded.end(); it++)
	{
		if (it->second.texId) {
			glDeleteTextures(1, &it->second.texId);
			it->second.texId = 0;
		}
	}
	m_loaded.clear();
}

GLuint TextureCache::LoadTexture(const GLchar* file)
{
	GLuint texId = 0;
	if (this->AddImage(file, texId)) {
		return texId;
	}
	return 0;
}

GLboolean TextureCache::AddImage(const GLchar* file, GLuint& texId)
{
	auto it = m_loaded.find(file);
	if (it != m_loaded.end())
	{
		texId = it->second.texId;
		return true;
	}

	FIBITMAP* fid = FreeImage_Load(FIF_JPEG, file);
	if (fid == NULL)
	{
		return GL_FALSE;
	}

	GLuint width = FreeImage_GetWidth(fid);
	GLuint height = FreeImage_GetHeight(fid);
	GLubyte* bits =  FreeImage_GetBits(fid);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	FreeImage_Unload(fid);

	m_loaded[file] = Texture(file, texId);
	return GL_TRUE;
}

void TextureCache::ErrorMsg(FREE_IMAGE_FORMAT fif, const char* msg)
{
	std::cout << "FreeImagError:" << msg << std::endl;
}