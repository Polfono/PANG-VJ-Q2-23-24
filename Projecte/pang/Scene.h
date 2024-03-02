#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BallManager.h"
#include "Text.h"
#include "Constants.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	int timer();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	BallManager* ballManager = BallManager::instance();
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int timeLeft = MAX_TIME;
	int timeInSecs = 0;
	Text textRenderer;

};


#endif // _SCENE_INCLUDE

