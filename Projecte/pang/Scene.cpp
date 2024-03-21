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

	// Init Food
	food = new Food();
	food->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	// Init PowerupsManager
	powerupsManager->setTileMap(map);

	// Init Projection
	currentHeight = SCREEN_HEIGHT;
	currentWidth = SCREEN_WIDTH;
	projection = glm::ortho(0.f, float(currentWidth) / ZOOM_FACTOR, float(currentHeight) / ZOOM_FACTOR, 0.f);
	glViewport(0, 0, currentWidth, currentHeight);

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
	//recorrer popScore y restar 1 a cada uno, si es 0, borrarlo
	for (auto it = popScore.begin(); it != popScore.end(); ++it) {
		--it->first;
		if (it->first == 0) {
			popScore.erase(it);
			break;
		}
	}

	currentTime += deltaTime;

	static bool wasTPressed = false;
	if (Game::instance().getKey(GLFW_KEY_T) && !wasTPressed) {
		wasTPressed = true;
		ballManager->dynamite();
	}
	if (!Game::instance().getKey(GLFW_KEY_T)) wasTPressed = false;

	static bool wasYPressed = false;
	if (Game::instance().getKey(GLFW_KEY_Y) && !wasYPressed) {
		wasYPressed = true;
		ballManager->freezeTime();
	}
	if (!Game::instance().getKey(GLFW_KEY_Y)) wasYPressed = false;

	static bool wasUPressed = false;
	if (Game::instance().getKey(GLFW_KEY_U) && !wasUPressed) {
		wasUPressed = true;
		player->invincibility();
	}
	if (!Game::instance().getKey(GLFW_KEY_U)) wasUPressed = false;

	static bool wasIPressed = false;
	if (Game::instance().getKey(GLFW_KEY_I) && !wasIPressed) {
		wasIPressed = true;
		ballManager->slowTime();
	}
	if (!Game::instance().getKey(GLFW_KEY_I)) wasIPressed = false;

	static bool wasOPressed = false;
	if (Game::instance().getKey(GLFW_KEY_O) && !wasOPressed) {
		wasOPressed = true;
		extraLife();
	}
	if (!Game::instance().getKey(GLFW_KEY_O)) wasOPressed = false;

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
		if (level < 17) {
			level++;
			setLevel(level);
		}
	}
	if(!Game::instance().getKey(GLFW_KEY_N)) wasNPressed = false;

	static bool wasBPressed = false;
	if (Game::instance().getKey(GLFW_KEY_B) && !wasBPressed && level > 1) {
		wasBPressed = true;
		if(level > 1) {
			level--;
			setLevel(level);
		}
	}
	if(!Game::instance().getKey(GLFW_KEY_B)) wasBPressed = false;

	// Level Selection with numbers
	static bool was1Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_1) && !was1Pressed) {
		setLevel(1);
	}
	if (!Game::instance().getKey(GLFW_KEY_1)) was1Pressed = false;

	static bool was2Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_2) && !was2Pressed) {
		setLevel(2);
	}
	if (!Game::instance().getKey(GLFW_KEY_2)) was2Pressed = false;

	static bool was3Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_3) && !was3Pressed) {
		setLevel(3);
	}
	if (!Game::instance().getKey(GLFW_KEY_3)) was3Pressed = false;

	static bool was4Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_4) && !was4Pressed) {
		setLevel(4);
	}
	if (!Game::instance().getKey(GLFW_KEY_4)) was4Pressed = false;

	static bool was5Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_5) && !was5Pressed) {
		setLevel(5);
	}
	if (!Game::instance().getKey(GLFW_KEY_5)) was5Pressed = false;

	static bool was6Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_6) && !was6Pressed) {
		setLevel(6);
	}
	if (!Game::instance().getKey(GLFW_KEY_6)) was6Pressed = false;

	static bool was7Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_7) && !was7Pressed) {
		setLevel(7);
	}
	if (!Game::instance().getKey(GLFW_KEY_7)) was7Pressed = false;

	static bool was8Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_8) && !was8Pressed) {
		setLevel(8);
	}
	if (!Game::instance().getKey(GLFW_KEY_8)) was8Pressed = false;

	static bool was9Pressed = false;
	if (Game::instance().getKey(GLFW_KEY_9) && !was9Pressed) {
		setLevel(9);
	}
	if (!Game::instance().getKey(GLFW_KEY_9)) was9Pressed = false;

	if (vidas < 0) {
		// GAME OVER SCENE //
		// hacer solo una vez
		if(vidas == -1) {
			SoundManager::instance().getSoundEngine()->play2D("sounds/GameOver.mp3", false);
		}

		--vidas;
		if (Game::instance().getKey(GLFW_KEY_ENTER)) { // Enter
			return true;
		}
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
				if(vidas >= 0) Level::instance().setMusicLevel(level);
				firstHit = false; // Después de los 2 segundos, ya no es la primera vez que hit es false
				hitTime = 0; // Reiniciar el contador de tiempo
			}
		}
		else {
			if (map->checkBrokenBlocks()) {
				map->doAnimations();
				map->prepareArrays(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			}

			if (player->update(deltaTime)) {
				hit = true;
				hitTime = 0; // Reiniciar el contador de tiempo cuando hit es true
				stageTime = int(currentTime);
			}

			score += food->update(player->getPosition());

			powerupsManager->update(player->getPosition());

			if (!ballManager->updateBalls()) {
				SoundManager::instance().getSoundEngine()->removeAllSoundSources();
				SoundManager::instance().getSoundEngine()->play2D("sounds/StageCompleted.mp3", false);

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
			SoundManager::instance().getSoundEngine()->removeAllSoundSources();

			firstHit = true;
			hitTime = 0;
			hit = false;
			timeLeft = 100;
			--vidas;
			map = Level::instance().LoadMapLevel(level);
			player->reset();
			ballManager->clearBalls();
			powerupsManager->clear();
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

		// Render Powerups
		powerupsManager->render();

		// Render Text
		// recorrer popScore y renderizar el score en su respectiva posicion
		for (auto it = popScore.begin(); it != popScore.end(); ++it) {
			textRenderer.render(it->second.first, glm::vec2(float(it->second.second.x * 2.5f), float(it->second.second.y * 2.5f)), 15, glm::vec4(1, 1, 0, 1));
		}

		std::string timeText = "TIME:";
		if (timeLeft < 100) timeText += "0";
		if (timeLeft < 10) timeText += "0";
		timeText += std::to_string(timeLeft);
		textRenderer.render(timeText, glm::vec2(round(11.0f/16.0f*currentWidth), round(1.0f/9.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));
		textRenderer.render("STAGE " + std::to_string(level), glm::vec2(round(25.0f/64.0f*currentWidth), round(85.0f/96.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));
		textRenderer.render(nameStage, glm::vec2(round(25.0f / 64.0f * currentWidth), round(15.0f/16.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));

		std::string scoreText = "SCORE:";
		if (score < 1000000) scoreText += "0";
		if (score < 100000) scoreText += "0";
		if (score < 10000) scoreText += "0";
		if (score < 1000) scoreText += "0";
		if (score < 100) scoreText += "0";
		if (score < 10) scoreText += "0";
		scoreText += std::to_string(score);
		textRenderer.render(scoreText, glm::vec2(round(5.0f/64.0f*currentWidth), round(35.0f/48.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));

		textRenderer.render("Vidas: " + std::to_string(vidas), glm::vec2(round(5.0f / 64.0f * currentWidth), round(25.0f/32.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));

		if (!hit && firstHit && vidas >= 0) {
			if (hitTime / 333 % 2 == 0)
				textRenderer.render("READY", glm::vec2(round(25.0f/64.0f*currentWidth), round(5.0f/12.0f*currentHeight)),round(currentWidth/20), glm::vec4(1, 1, 1, 1));
		}

		if(god) textRenderer.render("GOD MODE", glm::vec2(round(11.0f / 16.0f * currentWidth), round(35.0f / 48.0f * currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));
	}
	else if (changeStage) {
		bground->render(completedStage);

		textRenderer.render("STAGE " + std::to_string(level - 1) + " COMPLETED", glm::vec2(round(15.0f/64.0f*currentWidth), round(11.0f/16.0f*currentHeight)), round(currentWidth/32), glm::vec4(1, 1, 1, 1));
		textRenderer.render("TIME BONUS    " + std::to_string(scoreTime) + " PTS.", glm::vec2(round(13.0f/64.0f*currentWidth), round(19.0f/24.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));
		
		if (currentTime - stageTime >= 4000) {
			changeStage = false;
		}
	}
	else {
		textRenderer.render("GAME OVER", glm::vec2(round(35.0f/128.0f*currentWidth), round(5.0f/12.0f*currentHeight)), round(currentWidth/20), glm::vec4(1, 1, 1, 1));
		std::string scoreText = "SCORE:";
		if (score < 1000000) scoreText += "0";
		if (score < 100000) scoreText += "0";
		if (score < 10000) scoreText += "0";
		if (score < 1000) scoreText += "0";
		if (score < 100) scoreText += "0";
		if (score < 10) scoreText += "0";
		scoreText += std::to_string(score);
		textRenderer.render(scoreText, glm::vec2(round(53.0f/160.0f*currentWidth), round(25.0f/48.0f*currentHeight)), round(currentWidth / 40), glm::vec4(1, 1, 1, 1));
		textRenderer.render("PRESS 'ENTER' TO RETURN MENU", glm::vec2(round(7.0f/32.0f*currentWidth), round(15.0f/16.0f*currentHeight)), round(currentWidth/53), glm::vec4(1, 1, 1, 1));
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
	powerupsManager->clear();
	food->reset();
	Level::instance().LoadMapConfig(level, map, &scene, player, ballManager, &nameStage, food);

	timeLeft = 100;
}

void Scene::setLevel(int level) {
	SoundManager::instance().getSoundEngine()->removeAllSoundSources();
	hitTime = 0;
	firstHit = true;



	this->level = level;

	map = NULL;
	player->reset();
	hit = false;
	map = Level::instance().LoadMapLevel(level);
	food->reset();
	ballManager->clearBalls();
	powerupsManager->clear();
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

void Scene::extraLife() {
	vidas++;
}

void Scene::dynamite() {
	ballManager->dynamite();
}

void Scene::freezeTime() {
	ballManager->freezeTime();
}

void Scene::slowTime() {
	ballManager->slowTime();
}

void Scene::invincibility() {
	player->invincibility();
}

void Scene::addScore(int score) {
	this->score += score;
}

void Scene::addScoreCombo(int score, glm::vec2 pos) {
	popScore.push_back(make_pair(60, make_pair(std::to_string(score), pos)));
}

void Scene::resize(int width, int height) {
	int newWidth, newHeight;
	if (width / 4 >= height / 3) {
		newWidth = height * 4 / 3;
		newHeight = height;
	}
	else {
		newWidth = width;
		newHeight = width * 3 / 4;
	}

	// Calculate the offset to center the viewport
	int offsetX = (width - newWidth) / 2;
	int offsetY = (height - newHeight) / 2;

	currentHeight = newHeight;
	currentWidth = newWidth;

	// Set the viewport with the calculated dimensions and offset
	glViewport(offsetX, offsetY, newWidth, newHeight);
}