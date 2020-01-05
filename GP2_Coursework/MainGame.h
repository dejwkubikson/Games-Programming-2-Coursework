#pragma once
#include <SDL\SDL.h>
#include "camera.h"
#include <GL/glew.h>
#include "Display.h" 
#include "Texture.h"
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"

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

	Display _gameDisplay;
	GameState _gameState;

	/*Mesh mesh;
	Texture texture;
	Shader shader;
	Transform transform;
	*/

	GameObject monkey;
	GameObject monkey2;

	Camera myCamera;

	float counter;
};

