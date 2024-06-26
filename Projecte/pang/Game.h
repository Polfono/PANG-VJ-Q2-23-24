#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Constants.h"
#include "Menu.h"
#include "SoundManager.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	void resize(int width, int height);

	bool getKey(int key) const;

	void extraLife();
	void dynamite();
	void freezeTime();
	void slowTime();
	void invincibility();
	void addScore(int score);
	void addScoreCombo(int score, glm::vec2 pos);

private:
	bool start;
	int posIndex;
	int menuSection = 0;
	Menu* menu;
	bool bPlay; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time
	Scene scene;
	ISoundEngine* engine;

};


#endif // _GAME_INCLUDE


