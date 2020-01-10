#pragma once

#include <GL/glew.h>
#include <SDL\SDL.h>

class Skybox {

public:
	Skybox();
	~Skybox();

	// Initializes the skybox
	void initSkyBox();
	// Used to draw the skybox in the main game loop
	void drawSkyBox(float size);
	// Loads skybox textures and assigns to enum values
	unsigned int loadSkyBoxTexture(const char* filename);

private:

	enum { LEFT = 0, BACK, RIGHT, FRONT, TOP, BOTTOM };
	// Holds the textures
	unsigned int skybox[6];
};