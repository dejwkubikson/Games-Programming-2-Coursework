#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include "transform.h"
using namespace std;

class Shader
{
public:
	Shader();
	~Shader();

	// Sets GPU to use specified shaders
	void Bind();
	void Update(const Transform& transform, const Camera& camera);
	void Initialize(const string& filename);

	string LoadShader(const string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	GLuint CreateShader(const string& text, unsigned int type);

protected:
private:
	// Defining the number of shaders
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	// Tracking the shader program
	GLuint program;
	// Creating array of shaders
	GLuint shaders[NUM_SHADERS];
	// Creating number of uniform variables
	GLuint uniforms[NUM_UNIFORMS];
};
