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
#include "Food.h"

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

	// Completed Stage
	completedStage.loadFromFile("images/stageCompleted.png", TEXTURE_PIXEL_FORMAT_RGBA);

	// Init Player
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	// Init Ball Manager
	ballManager = BallManager::instance();

	// Init Food
	food = new Food();
	food->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

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
	food->reset();
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager, &nameStage, food);
}

bool Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	static bool wasGPressed = false;
	if (Game::instance().getKey(GLFW_KEY_G) && !wasGPressed) {
		wasGPressed = true;
		player->godMode();
		god = !god;
	}
	if(!Game::instance().getKey(GLFW_KEY_G)) wasGPressed = false;

	static bool wasNPressed = false;
	if (Game::instance().getKey(GLFW_KEY_N) && !wasNPressed) {
		wasNPressed = true;
		nextLevel();
	}
	if(!Game::instance().getKey(GLFW_KEY_N)) wasNPressed = false;

	static bool wasBPressed = false;
	if (Game::instance().getKey(GLFW_KEY_B) && !wasBPressed && level > 1) {
		level -= 2;
		wasBPressed = true;
		nextLevel();
	}
	if(!Game::instance().getKey(GLFW_KEY_B)) wasBPressed = false;

	if (vidas < 0) {
		// GAME OVER SCENE //
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		if (Game::instance().getKey(GLFW_KEY_ENTER)) // Enter
			return true;
	}
	
	if(timeLeft == 0) {
		// TIME OVER SCENE //
		hit = true;
	}

	if (!hit) {
		if (firstHit) { // Si es la primera vez que hit es false
			if(!changeStage) hitTime += deltaTime;

			// READY SCENE //

			if (hitTime >= 2000) { // Esperar 2 segundos
				firstHit = false; // Despu�s de los 2 segundos, ya no es la primera vez que hit es false
				hitTime = 0; // Reiniciar el contador de tiempo
			}
		}
		else {
			if (player->update(deltaTime)) {
				hit = true;
				hitTime = 0; // Reiniciar el contador de tiempo cuando hit es true
				stageTime = int(currentTime);
			}

			score += food->update();

			if (!ballManager->updateBalls()) {
				changeStage = true;
				stageTime = int(currentTime);
				scoreTime = timeLeft * 100;
				score += scoreTime;

				nextLevel();
			} 

			// Actualizar timer
			if (currentTime / 1000 >= 1) {
				if (timeLeft > 0) timeLeft--;
				currentTime = 0;
			}
		}
	}
	else {
		hitTime += deltaTime;
		player->die();
		if (hitTime >= 3000) { // 3000 milisegundos son 3 segundos
			firstHit = true;
			hitTime = 0;
			hit = false;
			timeLeft = 100;
			--vidas;
			player->reset();
			ballManager->clearBalls();
			food->reset();
			Level::instance().LoadMapConfig(level, map, &scene, player, ballManager, &nameStage, food);
		}
	}
	return false;
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

	if (vidas >= 0 && !changeStage) {
		
		// Render Background
		bground->render(scene);

		// Render TileMap
		map->render();

		// Render Player
		player->render();

		// Render Balls
		ballManager->renderBalls();

		// Render Food
		food->render();

		// Render Text
		std::string timeText = "TIME:";
		if (timeLeft < 100) timeText += "0";
		if (timeLeft < 10) timeText += "0";
		timeText += std::to_string(timeLeft);
		textRenderer.render(timeText, glm::vec2(440, 60), 17, glm::vec4(1, 1, 1, 1));
		textRenderer.render("STAGE " + std::to_string(level), glm::vec2(250, 425), 17, glm::vec4(1, 1, 1, 1));
		textRenderer.render(nameStage, glm::vec2(250, 450), 17, glm::vec4(1, 1, 1, 1));

		std::string scoreText = "SCORE:";
		if (score < 100000) scoreText += "0";
		if (score < 10000) scoreText += "0";
		if (score < 1000) scoreText += "0";
		if (score < 100) scoreText += "0";
		if (score < 10) scoreText += "0";
		scoreText += std::to_string(score);
		textRenderer.render(scoreText, glm::vec2(50, 350), 17, glm::vec4(1, 1, 1, 1));

		textRenderer.render("Vidas: " + std::to_string(vidas), glm::vec2(50, 375), 17, glm::vec4(1, 1, 1, 1));

		if (!hit && firstHit && vidas >= 0) {
			if (hitTime / 333 % 2 == 0)
				textRenderer.render("READY", glm::vec2(250, 200), 32, glm::vec4(1, 1, 1, 1));
		}

		if(god) textRenderer.render("GOD MODE", glm::vec2(440, 350), 17, glm::vec4(1, 1, 1, 1));
	}
	else if (changeStage) {
		bground->render(completedStage);

		textRenderer.render("STAGE " + std::to_string(level - 1) + " COMPLETED", glm::vec2(150, 330), 20, glm::vec4(1, 1, 1, 1));
		textRenderer.render("TIME BONUS    " + std::to_string(scoreTime) + " PTS.", glm::vec2(130, 380), 17, glm::vec4(1, 1, 1, 1));
		
		if (currentTime - stageTime >= 2000) {
			changeStage = false;
		}
	}
	else {
		textRenderer.render("GAME OVER", glm::vec2(175, 200), 32, glm::vec4(1, 1, 1, 1));
		std::string scoreText = "SCORE:";
		if (score < 100000) scoreText += "0";
		if (score < 10000) scoreText += "0";
		if (score < 1000) scoreText += "0";
		if (score < 100) scoreText += "0";
		if (score < 10) scoreText += "0";
		scoreText += std::to_string(score);
		textRenderer.render(scoreText, glm::vec2(215, 250), 17, glm::vec4(1, 1, 1, 1));
		textRenderer.render("PRESS 'ENTER' TO RETURN MENU", glm::vec2(140, 450), 12, glm::vec4(1, 1, 1, 1));
	}
}

void Scene::nextLevel() {
	hitTime = 0;
	firstHit = true;

	level++;
	if (level > 17) { // 17 niveles
		vidas = -1;
		return;
	}

	map = NULL;
	player->reset();
	hit = false;
	map = Level::instance().LoadMapLevel(level);
	ballManager->clearBalls();
	food->reset();
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager, &nameStage, food);

	timeLeft = 100;
}

void Scene::setLevel(int level) {
	hitTime = 0;
	firstHit = true;

	this->level = level;

	map = NULL;
	player->reset();
	hit = false;
	map = Level::instance().LoadMapLevel(level);
	food->reset();
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager, &nameStage, food);

	timeLeft = 100;
}

void Scene::reset() {
	hitTime = 0;
	firstHit = true;

	level = 1;
	vidas = 2;
	score = 0;
	hit = false;

	player->reset();
	ballManager->clearBalls();
	setLevel(1);
}