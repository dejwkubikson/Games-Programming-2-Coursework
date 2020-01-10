#pragma once
#include <string>
#include <GL\glew.h>
#include <cassert>
#include <iostream>

class Texture
{
public:
	Texture();
	void Initialize(const std::string& fileName);

	void Bind(unsigned int unit);

	~Texture();

protected:
private:

	GLuint textureHandler;
};

