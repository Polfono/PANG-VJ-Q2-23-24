#include "Level.h"
#include "TileMap.h"
#include "Constants.h"
#include "ShaderProgramManager.h"
#include "Scene.h"
#include "Player.h"
#include "BallManager.h"
#include "Food.h"
#include "SoundManager.h"
#include <iostream>

#define LEFT -1
#define RIGHT 1

Level::Level()
{
}

Level::~Level()
{
}

TileMap* Level::LoadMapLevel(int level)
{
	TileMap* map = TileMap::createTileMap("levels/level" + to_string(level) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), ShaderProgramManager::instance().getShaderProgram());
	return map;
}

// load scene from file, set player position and add balls to ballManager
void Level::LoadMapConfig(int level, TileMap* map, Texture* scene, Player* player, BallManager* ballManager, string* nameStage, Food* food)
{
	scene->loadFromFile("images/background" + to_string(level) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
	player->setTileMap(map);
	ballManager->setTileMap(map);
	food->setTileMap(map);

	// 17 levels
	if (level == 1) {
		*nameStage = "MT.FUJI";
		player->setPosition(glm::vec2(22 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(4 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
	} else if (level == 2) {
		*nameStage = "MT.KEIRIN";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(22 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(3 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
	}
	else if (level == 3) {
		*nameStage = "EMERALD TEMPLE";
		player->setPosition(glm::vec2(21 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(8 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);

		ballManager->addBall(glm::vec2(8 * map->getTileSize(), 12 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
		ballManager->addBall(glm::vec2(15 * map->getTileSize(), 12 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
		ballManager->addBall(glm::vec2(35 * map->getTileSize(), 12* map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, LEFT);
	}
	else if (level == 4) {
		*nameStage = "ANKOR WATT";
		player->setPosition(glm::vec2(22 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(33 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(23 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
	}
	else if (level == 5) {
		*nameStage = "AUSTRALIA";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));

		ballManager->addBall(glm::vec2(2 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(3 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(6 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
		ballManager->addBall(glm::vec2(8 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(8 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
		ballManager->addBall(glm::vec2(10 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(11 * map->getTileSize(), 4 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(12 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(13 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(14 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);

		ballManager->addBall(glm::vec2(16 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), MEDIUM, LEFT);
		ballManager->addBall(glm::vec2(19 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), MEDIUM, RIGHT);
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), MEDIUM, RIGHT);
	}
	else if (level == 6) {
		*nameStage = "TAJ MAHAL";
		player->setPosition(glm::vec2(22 * map->getTileSize(), 1 * map->getTileSize()));
		ballManager->addBall(glm::vec2(12 * map->getTileSize(), 1 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, LEFT);
		ballManager->addBall(glm::vec2(8 * map->getTileSize(), 9 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 9 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
	}
	else if (level == 7) {
		*nameStage = "LENINGRAD";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 19 * map->getTileSize()));
		ballManager->addBall(glm::vec2(22 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
	}
	else if (level == 8) {
		*nameStage = "PARIS";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
	}
	else if (level == 9) {
		*nameStage = "LONDON";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 15 * map->getTileSize()));
		ballManager->addBall(glm::vec2(19 * map->getTileSize(), 4 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
	}
	else if (level == 10) {
		*nameStage = "BARCELONA";
		player->setPosition(glm::vec2(21 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(42 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
		ballManager->addBall(glm::vec2(30 * map->getTileSize(), 10 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
		ballManager->addBall(glm::vec2(5 * map->getTileSize(), 10 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, LEFT);
		
	} else if (level == 11) {
		*nameStage = "ATHENS";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(38 * map->getTileSize(), 14 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
		ballManager->addBall(glm::vec2(1 * map->getTileSize(), 8 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
	}
	else if (level == 12) {
		*nameStage = "EGYPT";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(22 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 8 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, LEFT);
	}
	else if (level == 13) {
		*nameStage = "KENYA";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 2 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(6 * map->getTileSize(), 4 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
		ballManager->addBall(glm::vec2(32 * map->getTileSize(), 4 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);
	}
	else if (level == 14) {
		*nameStage = "NEW YORK";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(33 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(10 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
	}
	else if (level == 15) {
		*nameStage = "MAYA";

		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(22 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);

		ballManager->addBall(glm::vec2(13 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), LARGE, RIGHT);

		ballManager->addBall(glm::vec2(19 * map->getTileSize(), 7 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), MEDIUM, LEFT);

		ballManager->addBall(glm::vec2(15 * map->getTileSize(), 8 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
		ballManager->addBall(glm::vec2(16 * map->getTileSize(), 9 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(28 * map->getTileSize(), 8 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
		ballManager->addBall(glm::vec2(29 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
		ballManager->addBall(glm::vec2(33 * map->getTileSize(), 7 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, RIGHT);
		ballManager->addBall(glm::vec2(34 * map->getTileSize(), 6 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), SMALL, LEFT);
	}
	else if (level == 16) {
		*nameStage = "ANTARTICA";
		player->setPosition(glm::vec2(21 * map->getTileSize(), 3 * map->getTileSize()));
		ballManager->addBall(glm::vec2(22 * map->getTileSize(), 13 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(7 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
	}
	else if (level == 17) {
		*nameStage = "FASTER ISLAND";
		player->setPosition(glm::vec2(20 * map->getTileSize(), 21 * map->getTileSize()));
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 1 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 3 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, LEFT);
		ballManager->addBall(glm::vec2(21 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, RIGHT);
	}
}

void Level::setMusicLevel(int level) {
	if (level == 1) SoundManager::instance().getSoundEngine()->play2D("sounds/MtFuji.mp3", true);
	if (level == 2) SoundManager::instance().getSoundEngine()->play2D("sounds/MtKeirin.mp3", true);
	if (level == 3) SoundManager::instance().getSoundEngine()->play2D("sounds/EmeraldTemple_NewYork.mp3", true);
	if (level == 4) SoundManager::instance().getSoundEngine()->play2D("sounds/AngkorWat_Athens.mp3", true);
	if (level == 5) SoundManager::instance().getSoundEngine()->play2D("sounds/Australia_Kenya.mp3", true);
	if (level == 6) SoundManager::instance().getSoundEngine()->play2D("sounds/TajMahal_Egypt.mp3", true);
	if (level == 7) SoundManager::instance().getSoundEngine()->play2D("sounds/Leningrad_Antartica.mp3", true);
	if (level == 8) SoundManager::instance().getSoundEngine()->play2D("sounds/Paris.mp3", true);
	if (level == 9) SoundManager::instance().getSoundEngine()->play2D("sounds/London_Maya.mp3", true);
	if (level == 10) SoundManager::instance().getSoundEngine()->play2D("sounds/Barcelona_EasterIsland.mp3", true);
	if (level == 11) SoundManager::instance().getSoundEngine()->play2D("sounds/AngkorWat_Athens.mp3", true);
	if (level == 12) SoundManager::instance().getSoundEngine()->play2D("sounds/TajMahal_Egypt.mp3", true);
	if (level == 13) SoundManager::instance().getSoundEngine()->play2D("sounds/Australia_Kenya.mp3", true);
	if (level == 14) SoundManager::instance().getSoundEngine()->play2D("sounds/EmeraldTemple_NewYork.mp3", true);
	if (level == 15) SoundManager::instance().getSoundEngine()->play2D("sounds/London_Maya.mp3", true);
	if (level == 16) SoundManager::instance().getSoundEngine()->play2D("sounds/Leningrad_Antartica.mp3", true);
	if (level == 17) SoundManager::instance().getSoundEngine()->play2D("sounds/Barcelona_EasterIsland.mp3", true);
}