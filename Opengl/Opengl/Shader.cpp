#include "Shader.h"
#include<stdio.h>
#include<glm/gtc/type_ptr.hpp>
Shader::Shader(const GLchar* vertFile, const GLchar* fragFile) 
	: m_propgram(0)
{
	FILE* vHandle = NULL;
	fopen_s(&vHandle, vertFile, "rb");
	if (vHandle == nullptr) {
		printf("Load VertFile %s Failed!", vertFile);
		return;
	}

	fseek(vHandle, 0, SEEK_END);
	int vLen = ftell(vHandle);

	FILE* fHandle = NULL;
	fopen_s(&fHandle, fragFile, "rb");
	if (fHandle == nullptr) {
		printf("Load FragFile %s Failed!", fragFile);
		fclose(vHandle);
		return;
	}
	fseek(fHandle, 0, SEEK_END);
	int fLen = ftell(fHandle);
	
	int maxLen = vLen > fLen ? vLen : fLen;
	GLchar* buff = new char[maxLen + 1];
	
	fseek(vHandle, 0, SEEK_SET);
	fread(buff, 1, vLen, vHandle);
	buff[vLen] = '\0';

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &buff, &vLen);
	glCompileShader(vShader);
	GLint sucess = 0;
	char errinfo[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vShader, 512, NULL, errinfo);
		printf("%s\n", errinfo);
	}
	
	fseek(fHandle, 0, SEEK_SET);
	fread(buff, 1, fLen, fHandle);
	buff[fLen] = '\0';

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &buff, &fLen);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(fShader, 512, NULL, errinfo);
		printf("%s\n", errinfo);
	}

	m_propgram = glCreateProgram();
	glAttachShader(m_propgram, vShader);
	glAttachShader(m_propgram, fShader);
	glLinkProgram(m_propgram);
	glGetProgramiv(m_propgram, GL_LINK_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(m_propgram, 512, NULL, errinfo);
		printf("%s\n", errinfo);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	fclose(vHandle);
	fclose(fHandle);
	delete[] buff;
}

void Shader::Use()
{
	glUseProgram(m_propgram);
}

void Shader::SetMat4(const std::string& name, glm::mat4& m)
{
	GLint loc = glGetUniformLocation(m_propgram, name.c_str());
	if (loc != -1) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
	}
}
