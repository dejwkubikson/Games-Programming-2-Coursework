#include "Skybox.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
	glDeleteTextures(6, skybox);
}

void Skybox::initSkyBox()
{
	// Loading textures' ids to skybox array
	skybox[LEFT] = loadSkyBoxTexture("..\\res\\left.bmp");
	skybox[BACK] = loadSkyBoxTexture("..\\res\\back.bmp");
	skybox[RIGHT] = loadSkyBoxTexture("..\\res\\right.bmp");
	skybox[FRONT] = loadSkyBoxTexture("..\\res\\front.bmp");
	skybox[TOP] = loadSkyBoxTexture("..\\res\\top.bmp");
	skybox[BOTTOM] = loadSkyBoxTexture("..\\res\\bottom.bmp");
}

unsigned int Skybox::loadSkyBoxTexture(const char* fileName)
{
	// Creating variable to hold the id of the texture
	unsigned int id;
	glGenTextures(1, &id);
	// Loading BMP image
	SDL_Surface* texture = SDL_LoadBMP(fileName);
	glBindTexture(GL_TEXTURE_2D, id);
	// Linear filtering for minification (when texture is smaller than object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Linear filtering for magnification (when texture is larger than object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Repeating the pixels in the texture's edge in order to remove a white line at each edge of the cube.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      
	// Creating the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	// Deleting the image as it's no longer needed
	SDL_FreeSurface(texture);
	// Returning the id of the texture
	return id;
}

void Skybox::drawSkyBox(float size)
{
	// Disabling the lighting effects and z-buffering
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	// Creating front face
	glBindTexture(GL_TEXTURE_2D, skybox[FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();

	// Creating back face
	glBindTexture(GL_TEXTURE_2D, skybox[BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();

	// Creating left face
	glBindTexture(GL_TEXTURE_2D, skybox[LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();

	// Creating right face
	glBindTexture(GL_TEXTURE_2D, skybox[RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();

	// Creating top face
	glBindTexture(GL_TEXTURE_2D, skybox[TOP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, size / 2, -size / 2);
	glEnd();

	// Creating bottom face
	glBindTexture(GL_TEXTURE_2D, skybox[BOTTOM]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}