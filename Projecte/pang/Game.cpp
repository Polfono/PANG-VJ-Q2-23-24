#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "ShaderProgramManager.h"


void Game::init()
{
	ShaderProgramManager::instance().init();

	start = true;
	bPlay = true;
	posIndex = 0;

	glClearColor(0.f, 0.f, 0.f, 1.0f);

	menu = new Menu();
	menu->init(0);

	scene.init();
}

bool Game::update(int deltaTime)
{
	if (start)
	{
		scene.update(deltaTime);
	}
	else
	{
		menu->update(deltaTime);
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(start) scene.render();
	else menu->render();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;

	if (key == GLFW_KEY_DOWN) { //scroll menu down
		++posIndex;
		posIndex = (posIndex) % 4;
		menu->setPosIndex(posIndex);
	}
	if (key == GLFW_KEY_UP) { //scroll menu up
		--posIndex;
		if (posIndex < 0) posIndex = -3 * posIndex;
		posIndex = (posIndex) % 4;
		menu->setPosIndex(posIndex);
	}
	if (key == GLFW_KEY_ENTER) { //start game
		if(posIndex == 0) start = true;
		else if (posIndex == 3) bPlay = false;
	}



	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}



