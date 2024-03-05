#ifndef _ARPON_INCLUDE
#define _ARPON_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Ball.h"

class Arpon
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update();
	void render();

	void setTileMap(TileMap *tileMap);
	bool setPosition(const glm::vec2 &pos);
	bool checkCollision(Ball* ball);

private:
	glm::ivec2 tileMapDispl, posArpon;
	bool bThrowing = true;
	int altura = 0;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif

