#ifndef _BALL_INCLUDE
#define _BALL_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

const float GRAVEDAD = 0.075f;

enum BallSize {
	SMALL, MEDIUM, LARGE, EXTRA_LARGE
};

class Ball
{

	BallSize size;

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, BallSize size, int dir);
	void update();
	void render();
	void split();
	glm::ivec2 getSize();
	glm::vec2 getPosition();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posBall;
	int direction;
	float speed;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};

#endif