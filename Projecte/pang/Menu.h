#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"


class Menu {
public:
	Menu();
	~Menu();

	void init(const int& idScene);
	void render();
	void update(int deltaTime);
	void setPosIndex(int pos);

private:
	int id;
	Sprite* sprite1;
	Sprite* sprite2;
	TexturedQuad* bground;
	Texture spritesheet;
	glm::mat4 projection;
	Texture scene;
};

#endif // _MENU_INCLUDE