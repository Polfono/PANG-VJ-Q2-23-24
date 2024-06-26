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
	void godMode();
	void invincibility();

	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();
	
private:
	int delayShoot = 0;
	float speed = 0;
	bool subiendo = false;
	bool lastDir; // true right, false left
	bool delayClimb = false;

	bool god = false;
	bool escudoActivo = false;
	bool hitEscudo = false;
	int timerEscudo = 0;

	int delayDead = 30;
	bool fDead = true;
	bool fBounceDead = true;
	bool overIce = false;
	float horizontalSpeed = 0;
	int dDead;
	glm::ivec2 tileMapDispl, posPlayer;
	Arpon arpon;
	Texture spritesheet;
	Texture spritesheetEscudo;
	Sprite *sprite;
	Sprite* escudo;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


