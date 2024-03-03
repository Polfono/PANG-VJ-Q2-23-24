#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Constants.h"
#include "ShaderProgramManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	// Init shaders
	texProgram = ShaderProgramManager::instance().getShaderProgram();

	// Load level map
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	// Init player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	// Init balls
	ballManager = BallManager::instance();
	ballManager->setTileMap(map);
	ballManager->setShaderProgram(texProgram);
	ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
	ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);

	float zoomFactor = 1.425f;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH)/zoomFactor, float(SCREEN_HEIGHT)/zoomFactor, 0.f);

	// Init Writing
	textRenderer.init("fonts/PressStart2P-vaV7.ttf");
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	ballManager->updateBalls();

	// Actualizar timer
	if (currentTime / 1000 >= 1) {
		if(timeLeft > 0) timeLeft--;
		currentTime = 0;
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(0.5f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	ballManager->renderBalls();

	// Render Text
	std::string timeText = "TIME:";
	if (timeLeft < 100) timeText += "0";
	if (timeLeft < 10) timeText += "0";
	timeText += std::to_string(timeLeft);
	textRenderer.render(timeText, glm::vec2(445, 60), 16, glm::vec4(1, 1, 1, 1));
}