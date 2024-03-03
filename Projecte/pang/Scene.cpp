#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Constants.h"
#include "ShaderProgramManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Level.h"

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
	map = Level::instance().LoadMapLevel(level);

	// Init shaders
	texProgram = ShaderProgramManager::instance().getShaderProgram();

	// Init Background
	glm::vec2 geom[2] = { glm::vec2(32.f, 16.f), glm::vec2(416, 224) }; // Quad size
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) }; // Texture coordinates
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());

	// Init Player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	// Init Ball Manager
	ballManager = BallManager::instance();

	// Init Projection
	float zoomFactor = 1.425f;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH) / zoomFactor, float(SCREEN_HEIGHT) / zoomFactor, 0.f);

	// Init Writing
	textRenderer.init("fonts/PressStart2P-vaV7.ttf");

	// Cada nivel
	// -- Background
	// -- TileMap
	// -- Player Position
	// -- addBalls BallManager

	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	if (!ballManager->updateBalls()) nextLevel();

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

	// Render Background
	bground->render(scene);

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

void Scene::nextLevel() {
	level++;
	if(level > 17) // end

	map = Level::instance().LoadMapLevel(level);
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager);

	timeLeft = 90;
}

void Scene::setLevel(int level) {
	this->level = level;
	map = Level::instance().LoadMapLevel(level);
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager);

	timeLeft = 90;
}