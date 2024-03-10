#include "PowerupsManager.h"
#include "Game.h"
#include "ShaderProgramManager.h"

PowerupsManager* PowerupsManager::s_inst = nullptr;

void PowerupsManager::addPowerup(glm::vec2 pos, const glm::ivec2& tileMapDispl)
{
	Powerup* powerup = new Powerup();
	powerup->init(pos, tileMapDispl, ShaderProgramManager::instance().getShaderProgram());
	powerup->setTileMap(map);
	powerups.push_back(powerup);
}

void PowerupsManager::removePowerup(Powerup* powerup)
{
	for (auto it = powerups.begin(); it != powerups.end(); ++it)
	{
		if (*it == powerup)
		{
			powerups.erase(it);
			delete powerup;
			break;
		}
	}
}

void PowerupsManager::update(glm::vec2 posPlayer)
{
	if (powerups.empty())
		return;

	for (auto& powerup : powerups)
	{
		powerup->update(posPlayer);
	}
}

void PowerupsManager::render()
{
	for (auto& powerup : powerups)
	{
		powerup->render();
	}
}

void PowerupsManager::clear()
{
	for (auto& powerup : powerups)
	{
		delete powerup;
	}
	powerups.clear();
}

void PowerupsManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}




