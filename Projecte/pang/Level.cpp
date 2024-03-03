#include "Level.h"
#include "TileMap.h"
#include "Constants.h"
#include "ShaderProgramManager.h"
#include "Scene.h"
#include "Player.h"
#include "BallManager.h"
#include <iostream>

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
void Level::LoadMapConfig(int level, TileMap* map, Texture* scene, Player* player, BallManager* ballManager)
{
	scene->loadFromFile("images/background" + to_string(level) + ".png", TEXTURE_PIXEL_FORMAT_RGBA);
	player->setTileMap(map);
	ballManager->setTileMap(map);

	// 17 levels
	if (level == 1) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	} else if (level == 2) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 3) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 4) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 5) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 6) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 7) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 8) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 9) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 10) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	} else if (level == 11) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 12) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 13) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 14) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 15) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 16) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
	else if (level == 17) {
		player->setPosition(glm::vec2(22 * map->getTileSize(), 20 * map->getTileSize()));
		ballManager->addBall(glm::vec2(27 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, 1);
		ballManager->addBall(glm::vec2(18 * map->getTileSize(), 5 * map->getTileSize()), glm::ivec2(SCREEN_X, SCREEN_Y), EXTRA_LARGE, -1);
	}
}
