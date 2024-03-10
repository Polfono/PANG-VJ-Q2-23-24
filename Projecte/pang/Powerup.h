#ifndef POWERUP_H
#define POWERUP_H

#include "Sprite.h"
#include "TileMap.h"
#include "Constants.h"
#include "SoundManager.h"

enum PowerupType {
	DYNAMITE, FREEZETIME,  INVINCIBILITY, SLOWTIME, EXTRALIFE
};

class Powerup
{
	PowerupType type;

public:

	void init(glm::vec2 pos, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update();
	void render();
	void setTileMap(TileMap* tileMap);
	void checkCollision(glm::vec2 posPlayer);

private:

	glm::ivec2 tileMapDispl, posPowerup;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int timeCounter = 0;
	bool blinking = false;
};

#endif // POWERUP_H