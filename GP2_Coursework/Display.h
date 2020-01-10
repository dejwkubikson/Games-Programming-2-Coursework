#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class Display
{
public:
	Display();
	~Display();

	void initDisplay();
	// Swaps the buffers
	void swapBuffer();
	// Clears the display
	void clearDisplay(float r, float g, float b, float a);
	// Returns screen width
	float getScreenWidth();
	// Returns screen height
	float getScreenHeight();

	// Used to display fog
	void displayFog();
	// Used to display light effect
	void displayLight();

private:

	// Error handling
	void returnError(string errorString);
	
	// Global variable to hold the context
	SDL_GLContext glContext;
	// Holds the pointer to the window
	SDL_Window* sdlWindow;
	float screenWidth;
	float screenHeight;

	// Light settings
	// w component in lightpos set to 0.0f to be treated as directional light source
	GLfloat lightpos[4] = { 15.0f, 15.0f, 0.0f, 0.0f };
	GLfloat ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };
};

