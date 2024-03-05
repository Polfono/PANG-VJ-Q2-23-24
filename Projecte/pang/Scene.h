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
	void setLevel(int level);
	void nextLevel();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	BallManager* ballManager = BallManager::instance();
	ShaderProgram texProgram;
	glm::mat4 projection;
	int timeLeft = 100;
	float currentTime = 0.0f; 
	Text textRenderer;
	TexturedQuad* bground;
	Texture scene;
	int level = 1;
	int vidas = 3;
	bool hit = false;
	string nameStage;
	int score = 0;
	int hitTime = 0;
	bool firstHit = true;

};


#endif // _SCENE_INCLUDE

