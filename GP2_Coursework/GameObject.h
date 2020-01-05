#pragma once
#include "Texture.h"
#include "transform.h"
#include "Shader.h"
#include "stb_image.h"
#include <cassert>
#include <GL\glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "obj_loader.h"
#include "Mesh.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void LoadModel(const std::string& filename);
	void LoadTexture(const std::string& filename);
	void LoadShader(const std::string& filename);

	Mesh mesh;
	Texture texture;
	Shader shader;
	Transform transform;
};