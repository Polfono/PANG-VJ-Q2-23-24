#ifndef POWERUPSMANAGER_H
#define POWERUPSMANAGER_H

#include "Powerup.h"
#include <vector>

class PowerupsManager
{
	vector<Powerup*> powerups;
	static PowerupsManager* s_inst;
	TileMap* map;
	glm::ivec2 tileMapDispl;

public:
	static PowerupsManager* instance()
	{
		if (s_inst == nullptr)
		{
			s_inst = new PowerupsManager();
		}
		return s_inst;
	}

	void addPowerup(glm::vec2 pos, const glm::ivec2& tileMapPos);
	void removePowerup(Powerup* powerup);
	void update(glm::vec2 posPlayer);
	void render();
	void clear();

	void setTileMap(TileMap* tileMap);
};

#endif // POWERUPSMANAGER_H
