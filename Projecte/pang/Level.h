#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "TileMap.h"
#include "Player.h"
#include "BallManager.h"
#include "Texture.h"

class Level
{
public:
	static Level& instance() {
		static Level L;
		return L;
	}

	Level();
	~Level();
	TileMap* LoadMapLevel(int level);
	void LoadMapConfig(int level, TileMap* map, Texture* scene, Player* player, BallManager* ballManager, string* nameStage);
};

#endif // _LEVEL_INCLUDE