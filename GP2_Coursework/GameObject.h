#pragma once
#include "Texture.h"
#include "transform.h"
#include "Shader.h"
#include <cassert>
#include <GL\glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "obj_loader.h"
#include "Mesh.h"

using namespace std;

// Gameobject class created for easier access to each objects mesh, texture and transform.
class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void LoadModel(const string& fileName);
	void LoadTexture(const string& fileName);

	Mesh mesh;
	Texture texture;
	Transform transform;
};