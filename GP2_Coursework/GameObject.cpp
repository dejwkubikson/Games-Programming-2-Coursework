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
}

void GameObject::LoadModel(const string& fileName)
{
	// Loading model through Mesh class
	mesh.loadModel(fileName);
}


void GameObject::LoadTexture(const string& fileName)
{
	// Loading texture through Texture class
	texture.Initialize(fileName);
}
