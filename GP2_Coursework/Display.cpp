#include "Display.h"


Display::Display()
{
	// Initialising to generate null access violation for debugging
	sdlWindow = nullptr;
	screenWidth = 1024.0f;
	screenHeight = 768.0f; 
}

Display::~Display()
{
	// Deleting context
	SDL_GL_DeleteContext(glContext);
	// Deleting SDL window after the context
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void Display::initDisplay()
{
	// Initalizing all SDL subsystems
	SDL_Init(SDL_INIT_EVERYTHING);

	// Minimum number of bits used to display colours
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Creating the window in the centre of user's screen
	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);

	// Enabling z-buffering
	glEnable(GL_DEPTH_TEST);
	// Setting faces that are not visible to camera to not render
	glEnable(GL_CULL_FACE);

	if (sdlWindow == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void Display::swapBuffer()
{
	// Updating a window with OpenGL rendering.
	SDL_GL_SwapWindow(sdlWindow);
}

void Display::clearDisplay(float r, float g, float b, float a)
{
	// Clearing colour and depth buffers
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Display::getScreenWidth()
{
	return screenWidth;
}

float Display::getScreenHeight()
{
	return screenHeight;
}

void Display::displayFog()
{
	glLoadIdentity();
	// Using GL_MODELVIEW as it 'defines' objects in the scene
	glMatrixMode(GL_MODELVIEW);
	// Enabling fog
	glEnable(GL_FOG);
	// Setting the fog to highest visual effect
	glHint(GL_FOG_HINT, GL_NICEST);
	// Making the fog density higher when further from camera (exponential fog gives a natural feel)
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.3f);
	// Setting the fog colour to grey
	float fogColour[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColour);
}

void Display::displayLight()
{
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	// Enabling the light effect
	glEnable(GL_LIGHTING);
	// Setting the ambient, diffues, and specular intensity of the light (RGBA)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	// Transfered by the GL_MODELVIEW matrix
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

void Display::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}