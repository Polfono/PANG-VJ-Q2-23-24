#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"
#include "Constants.h"

class Menu {
public:
	Menu();
	~Menu();

	void init(const int& idScene);
	void render(int n);
	void update(int deltaTime);
	void setPosIndex(int pos);

private:
	int id;
	Sprite* sprite1;
	Sprite* sprite2;
	TexturedQuad* bground;
	Texture spritesheet;
	glm::mat4 projection;
	Texture menu;
	Texture credits;
	Texture instructions1;
	Texture instructions2;
	int currentWidth = SCREEN_WIDTH;
	int currentHeight = SCREEN_HEIGHT;
};

#endif // _MENU_INCLUDE