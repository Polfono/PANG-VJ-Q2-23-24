#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BallManager.h"
#include "Text.h"
#include "Constants.h"
#include "Food.h"
#include "PowerupsManager.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	bool update(int deltaTime);
	void render();
	int timer();
	void setLevel(int level);
	void nextLevel();
	void reset();
	void extraLife();
	void dynamite();
	void freezeTime();
	void slowTime();
	void invincibility();
	void addScore(int score);
	void addScoreCombo(int score, glm::vec2 pos);
	void resize(int width, int height);

private:
	void initShaders();

private:
	TileMap* map;
	Player *player;
	Food *food;
	PowerupsManager* powerupsManager = PowerupsManager::instance();
	BallManager* ballManager = BallManager::instance();
	ShaderProgram texProgram;
	glm::mat4 projection;
	int timeLeft = 100;
	float currentTime = 0.0f; 
	Text textRenderer;
	TexturedQuad* bground;
	Texture scene;
	Texture completedStage;
	Texture life;
	Sprite* lifeSprite;
	bool win = false;
	int level = 1;
	int vidas = 2;
	bool hit = false;
	string nameStage;
	int score = 0;
	int hitTime = 0;
	bool firstHit = true;
	bool changeStage = false;
	int stageTime;
	int scoreTime;
	bool god = false;
	int currentWidth;
	int currentHeight;

	// initialize empty
	vector <pair<int, pair<string, glm::vec2>>> popScore = vector <pair<int, pair<string, glm::vec2>>>();
};


#endif // _SCENE_INCLUDE

