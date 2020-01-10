#pragma once
#include "MainGame.h"

MainGame::MainGame()
{
	// Locking the mouse in the centre of the screen
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// Setting the game state to play
	_gameState = GameState::PLAY;
	// Creating new display
	Display* _gameDisplay = new Display();
	// Creating new shader, audio device and skybox
	Shader* shader();
	Audio* audioDevice();
	Skybox* skybox();
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
	// Initializing all components
	_gameDisplay.initDisplay(); 

	// Objects
	crate.LoadModel("..\\res\\crate.obj");
	crate.LoadTexture("..\\res\\wood_texture.jpg");
	// Mesh sphere can only be set once. It doesn't have to in the game loop because the objects aren't moving
	crate.mesh.updateSphereData(glm::vec3(5, -3, 20), 3);

	plasticBox.LoadModel("..\\res\\plastic_crate.obj");
	plasticBox.LoadTexture("..\\res\\plastic_texture.jpg");
	plasticBox.mesh.updateSphereData(glm::vec3(-5, -8, 20), 3);

	barrier.LoadModel("..\\res\\barrier.obj");
	barrier.LoadTexture("..\\res\\barrier_texture.jpg");
	barrier.mesh.updateSphereData(glm::vec3(0, -6, 10), 3);

	// Shader
	shader.Initialize("..\\res\\shader");

	// Skybox
	skybox.initSkyBox();

	// Camera
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getScreenWidth() / _gameDisplay.getScreenHeight(), 0.01f, 1000.0f);

	// Audio
	bgMusic = audioDevice.loadSound("..\\res\\bg_music.wav");
	collisionSound = audioDevice.loadSound("..\\res\\collision_sound.wav");
}

void MainGame::processInput()
{
	SDL_Event evnt;

	// Get and process events
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN:
			// The player can use W, A, S and D keys to move around
			if (evnt.key.keysym.sym == SDLK_w)
				myCamera.MoveForward(0.2f);

			if (evnt.key.keysym.sym == SDLK_d)
				myCamera.MoveRight(-0.2f);

			if (evnt.key.keysym.sym == SDLK_s)
				myCamera.MoveForward(-0.2f);

			if (evnt.key.keysym.sym == SDLK_a)
				myCamera.MoveRight(0.2f);

			// On 'ESC' press exiting the game
			if (evnt.key.keysym.sym == SDLK_ESCAPE)
				_gameState = GameState::EXIT;

			break;

		case SDL_MOUSEMOTION:
			// Using mouse motion to rotate the camera
			myCamera.RotateY(evnt.motion.yrel * 0.003f);
			myCamera.RotateX(-evnt.motion.xrel * 0.003f);
			break;

		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		// Processing input first
		processInput();

		// Play background music
		playAudio(bgMusic, glm::vec3(0.0f, 0.0f, 0.0f));

		// Drawing the game
		drawGame();

		// Checking for collisions
		if (collision(myCamera.collider.getSpherePos(), myCamera.collider.getSphereRadius(), barrier.mesh.getSpherePos(), barrier.mesh.getSphereRadius()))
			cout << "Collided with a barrier! " << endl;
		if (collision(myCamera.collider.getSpherePos(), myCamera.collider.getSphereRadius(), plasticBox.mesh.getSpherePos(), plasticBox.mesh.getSphereRadius()))
			cout << "Collided with a plastic box! " << endl;
		if (collision(myCamera.collider.getSpherePos(), myCamera.collider.getSphereRadius(), crate.mesh.getSpherePos(), crate.mesh.getSphereRadius()))
			cout << "Collided with a crate! " << endl;
	}
}

bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	// Calculating the distance difference from two spheres
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	// If the distance is less than sum of two radiuses then a collision occured
	if (distance < (m1Rad + m2Rad))
	{
		// Playing sound on collision
		audioDevice.setlistener(myCamera.getPos(), m1Pos);
		playAudio(collisionSound, m1Pos);
		return true;
	}
	else
		return false;
}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos);
	}
}

void MainGame::drawGame()
{
	// Clearing the display
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// Displaying fog and light
	_gameDisplay.displayFog();
	_gameDisplay.displayLight();

	// Drawing skybox
	skybox.drawSkyBox(1200);

	// Binding the shader
	shader.Bind();
	{
		// Drawing each object
		crate.transform.SetPos(glm::vec3(5, -3, 20));
		crate.transform.SetRot(glm::vec3(0, 0.5f, 0));
		crate.transform.SetScale(glm::vec3(2, 2, 2));
		shader.Update(crate.transform, myCamera);
		crate.texture.Bind(0);
		crate.mesh.draw();

		plasticBox.transform.SetPos(glm::vec3(-5, -8, 20));
		plasticBox.transform.SetRot(glm::vec3(4.6f, 0, 0.5f));
		plasticBox.transform.SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
		shader.Update(plasticBox.transform, myCamera);
		plasticBox.texture.Bind(0);
		plasticBox.mesh.draw();

		barrier.transform.SetPos(glm::vec3(0, -6, 10));
		barrier.transform.SetRot(glm::vec3(0.0f, 0, 0.0f));
		barrier.transform.SetScale(glm::vec3(0.04f, 0.04f, 0.04f));
		shader.Update(barrier.transform, myCamera);
		barrier.texture.Bind(0);
		barrier.mesh.draw();
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
} 