#include <GL/glew.h>nnn
#include <GLFW/glfw3.h>
#include "Game.h"
#include "ShaderProgramManager.h"
#include <iostream>


void Game::init()
{
	SoundManager::instance().init();
	engine = SoundManager::instance().getSoundEngine();
	engine->play2D("sounds/Menu.mp3", true, false);

	ShaderProgramManager::instance().init();

	start = false;
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
		if (scene.update(deltaTime))
		{
			scene.reset();
			engine->play2D("sounds/Menu.mp3", true, false);
			start = false;
		}
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
	if (start) scene.render();
	else menu->render(menuSection);
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
	if (key == GLFW_KEY_ENTER && start == false) { //start game
		engine->play2D("sounds/Select.mp3", false, false);
		if (menuSection != 0) {
			if(menuSection == 1) menuSection = 2;
			else menuSection = 0;
		}
		else {
			if (posIndex == 0) {
				engine->removeSoundSource("sounds/Menu.mp3");
				start = true;
			} 
			else if (posIndex == 1) {
				menuSection = 1;
			}
			else if (posIndex == 2) {
				menuSection = 3;
			}
			else if (posIndex == 3) bPlay = false;
		}
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

void Game::extraLife()
{
	scene.extraLife();
}

void Game::dynamite()
{
	scene.dynamite();
}

void Game::freezeTime()
{
	scene.freezeTime();
}

void Game::slowTime()
{
	scene.slowTime();
}

void Game::resize(int width, int height)
{
	scene.resize(width, height);
}

void Game::invincibility()
{
	scene.invincibility();
}

void Game::addScore(int score)
{
	scene.addScore(score);
}

void Game::addScoreCombo(int score, glm::vec2 pos)
{
	scene.addScoreCombo(score, pos);
}