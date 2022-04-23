#pragma once
#include<glad/glad.h>
#include<string>
#include<glm/glm.hpp>
class Shader
{
public :
	Shader(const GLchar* vertFile, const GLchar* fragFile);

	void Use();

	void SetMat4(const std::string& name, glm::mat4& m);

	GLuint m_propgram;
};

