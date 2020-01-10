#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		// Removing the shader from the program
		glDetachShader(program, shaders[i]);
		// Deleting the shaders
		glDeleteShader(shaders[i]);
	}
	// Deleting the program
	glDeleteProgram(program);
}

void Shader::Initialize(const string& filename)
{
	// Creating shader program (OpenGL saves as ref number)
	program = glCreateProgram();
	// Loading Vertex shader
	shaders[0] = CreateShader(LoadShader("..\\res\\shader.vert"), GL_VERTEX_SHADER);
	// Loading fragment shader
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		// Adding all shaders to the program
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord"); 

	// Creating executables that will run on the GPU shaders
	glLinkProgram(program);
	// Checking for error
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	// Checking if the entire program is valid
	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	// Associating with the location of uniform variable within a program
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

void Shader::Bind()
{
	// Installing the program object specified by program as part of the rendering state
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Shader::CreateShader(const string& text, unsigned int type)
{
	// Creating shader based on specified type
	GLuint shader = glCreateShader(type);

	// Checking if shader was created (0 means no)
	if (shader == 0)
		std::cerr << "Error type creation failed " << type << std::endl;

	// Converting strings into list of c-strings
	const GLchar* stringSource[1];
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	// Sending source code to OpenGL
	glShaderSource(shader, 1, stringSource, lengths);
	// Telling OpenGL to compile the shader's code
	glCompileShader(shader);

	// Checking for error
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

std::string Shader::LoadShader(const string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

