#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Arpon.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	bool update(int deltaTime);
	void die();
	void render();
	bool checkCollision(Ball* ball);
	void reset();

	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	int delayShoot = 0;
	float speed = 0;

	int delayDead = 30;
	bool fDead = true;
	bool fBounceDead = true;
	int dDead;
	glm::ivec2 tileMapDispl, posPlayer;
	Arpon arpon;
	Texture spritesheet;
	Sprite *sprite;
	Sprite *spriteDead;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


