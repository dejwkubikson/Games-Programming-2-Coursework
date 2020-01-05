#pragma once
#include "MainGame.h"
#include <iostream>
#include <string>

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	/*Mesh* mesh();
	Texture* texture();
	Shader* shader();
	Transform* transform();*/

	//GameObject* monkey();

	counter = 0.0f;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 

	/*mesh.loadModel("..\\res\\monkey3.obj");
	texture.Initialize("..\\res\\bricks.jpg");
	shader.Initialize("..\\res\\shader");*/

	monkey.LoadModel("..\\res\\monkey3.obj");
	monkey.LoadTexture("..\\res\\bricks.jpg");
	monkey.LoadShader("..\\res\\shader");

	monkey2.LoadModel("..\\res\\monkey3.obj");
	monkey2.LoadTexture("..\\res\\Water.jpg");
	monkey2.LoadShader("..\\res\\shader");

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getScreenWidth() / _gameDisplay.getScreenHeight(), 0.01f, 1000.0f);

	counter = 0.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_KEYDOWN:
				if (evnt.key.keysym.sym == SDLK_w)
					myCamera.MoveForward(0.2f);

				if (evnt.key.keysym.sym == SDLK_d)
					myCamera.MoveRight(-0.2f);

				if (evnt.key.keysym.sym == SDLK_s)
					myCamera.MoveForward(-0.2f);

				if (evnt.key.keysym.sym == SDLK_a)
					myCamera.MoveRight(0.2f);

				if (evnt.key.keysym.sym == SDLK_e)
					myCamera.RotateY(-0.1f);

				if (evnt.key.keysym.sym == SDLK_q)
					myCamera.RotateY(0.1f);
			break;

			case SDL_MOUSEMOTION:
				myCamera.SetXViewProjection(evnt.motion.xrel);
				myCamera.SetYViewProjection(evnt.motion.yrel);
				break;

			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	/*transform.SetPos(glm::vec3(sinf(counter), 0.0f, 0.0f));
	transform.SetRot(glm::vec3(0.0f, 180, 0.0f));
	//transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);

	mesh.draw();*/

	monkey.transform.SetPos(glm::vec3(sinf(counter), 0.0f, 0.0f));
	monkey.transform.SetRot(glm::vec3(0.0f, 180, 0.0f));
	monkey.shader.Bind();
	monkey.shader.Update(monkey.transform, myCamera);
	monkey.texture.Bind(0);
	monkey.mesh.draw();

	monkey2.transform.SetPos(glm::vec3(sinf(counter), 0.0f, 5.0f));
	monkey2.transform.SetRot(glm::vec3(0.0f, 180, 0.0f));
	monkey2.shader.Bind();
	monkey2.shader.Update(monkey2.transform, myCamera);
	monkey2.texture.Bind(0);
	monkey2.mesh.draw();

	counter += 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
} 