#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "camera.h"
#include "Display.h" 
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"
#include "Audio.h"
#include "Skybox.h"


enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	// Creates a listener for the audio device and uses the Audio class to play sound
	void playAudio(unsigned int Source, glm::vec3 pos);
	// Checks for collisions. Returns true if a collision between camera and another object occured
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	Display _gameDisplay;
	GameState _gameState;
	Camera myCamera;

	GameObject crate;
	GameObject plasticBox;
	GameObject barrier;
	Shader shader;
	Skybox skybox;
	Audio audioDevice;

	unsigned int bgMusic;
	unsigned int collisionSound;
};

