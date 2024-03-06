#include "Food.h"
#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <map>
#include <ctime>

map<FoodType, int> points =
{
	{CHERRIES, 500}, {LEMON, 1000}, {BANANA, 2000}, {ORANGE, 3000}, {WATERMELON, 4000}, {PINEAPPLE, 5000}, {GRAPES, 6000}, {APPLE, 7000}, {STRAWBERRY, 8000}, {HONEYDEW, 9000}, {PICKLE, 10000},
	{EGGPLANT, 12000}, {TOMATO, 14000}, {SQUASH, 16000}, {CARROT, 18000}, {CORN, 20000}, {GREENPEPPER, 22000}, {RADISH, 24000}, {MUSHROOM, 26000}, {BEAN, 28000}, {HAMBURGER, 30000}, {HOTDOG, 33000},
	{WIENERONASTICK, 36000}, {DOUGHNUT, 39000}, {CHICKENDRUMSTICK, 42000}, {FRENCHFRIES, 45000}, {SHRIMPNIGIRI, 48000}, {CAKE, 50000}
};	

void Food::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/food.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::ivec2(30, 30), glm::vec2(0.1, 0.34), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(30);
	
	for (int i = 0; i < 29; i++)
	{
		sprite->setAnimationSpeed(i, 8);
		sprite->addKeyframe(i, glm::vec2(0.0f + 0.1f* (i % 10), 0.0f + (i/10)*0.34f));
	}
		

	sprite->changeAnimation(28);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFood.x), float(tileMapDispl.y + posFood.y)));
}

int Food::update()
{
	if (--secToAppear < 0) {
		sprite->changeAnimation(type);
		posFood.y += 1.75f;
		map->collisionMoveDownPlayer(posFood, glm::ivec2(30, 30), &posFood.y);
	}

	// si toca al jugador
	if (false) return points[type];
	

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFood.x), float(tileMapDispl.y + posFood.y)));
	return 0;
}

void Food::render()
{
	sprite->render();
}

void Food::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Food::reset()
{
	// random type using time seed
	srand(time(NULL));
	type = FoodType(rand() % 28);

	// random number between 10 and 30
	secToAppear = (rand() % 20 + 10)*60;
	//secToAppear = 0;

	sprite->changeAnimation(28);
	
	posFood = glm::ivec2(rand()%300+30, 5);
}




