#ifndef FOOD_H
#define FOOD_H

#include "Sprite.h"
#include "TileMap.h"
#include "Constants.h"

enum FoodType {
	CHERRIES, LEMON, BANANA, ORANGE, WATERMELON, PINEAPPLE, GRAPES, APPLE, STRAWBERRY, HONEYDEW, PICKLE,
	EGGPLANT, TOMATO, SQUASH, CARROT, CORN, GREENPEPPER, RADISH, MUSHROOM, BEAN, HAMBURGER, HOTDOG,
	WIENERONASTICK, DOUGHNUT, CHICKENDRUMSTICK, FRENCHFRIES, SHRIMPNIGIRI, CAKE
};

class Food
{
	FoodType type;	

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	int update();
	void render();
	void setTileMap(TileMap* tileMap);
	void reset();

private:
	glm::ivec2 tileMapDispl, posFood;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int secToAppear = 0;
};

#endif // FOOD_H

