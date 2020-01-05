#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	// Deleting mesh
	mesh.~Mesh();
	// Deleting texture
	texture.~Texture();
	// Deleting shader
	shader.~Shader();
}

void GameObject::LoadModel(const std::string& filename)
{
	mesh.loadModel(filename);
}


void GameObject::LoadTexture(const std::string& filename)
{
	texture.Initialize(filename);
}


void GameObject::LoadShader(const std::string& filename)
{
	shader.Initialize(filename);
}
