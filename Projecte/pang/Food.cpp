#include "Food.h"
#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>

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

int Food::update(glm::vec2 posPlayer)
{
	if (--secToAppear < 0) {
		timeCounter++;

		if (timeCounter > 600) { // 10 segundos
			consumed = true;
		}

		// Si el contador de tiempo es mayor que 7 segundos
		if (timeCounter > 420) {
			blinking = true;
		}

		if (blinking && timeCounter % 30 == 0) {
			sprite->changeAnimation(28);
		}
		else if (blinking && timeCounter % 30 == 15) {
			sprite->changeAnimation(type);
		}

		// gravedad
		posFood.y += 1.75f;
		map->collisionMoveDownPlayer(posFood, glm::ivec2(30, 30), &posFood.y);

		// si esta en medio de una pared
		if (map->tileInRegion(posFood, glm::ivec2(30, 30))) {
			consumed = true; posFood = glm::ivec2(rand() % 300 + 30, 7);
		}
		else {
			// no aparece hasta que no este fuera de una pared
			if (!animationAssigned) {
				sprite->changeAnimation(type);
				animationAssigned = true;
				consumed = false;
			}
		}

	}

	// si toca al jugador consumir
	if (!consumed && posPlayer.x + 15 > posFood.x && posPlayer.x < posFood.x + 15 && posPlayer.y + 32 > posFood.y && posPlayer.y < posFood.y + 15) {
		consumed = true;
		SoundManager::instance().getSoundEngine()->play2D("sounds/item.mp3", GL_FALSE);
		return points[type];
	}
	

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFood.x), float(tileMapDispl.y + posFood.y)));
	return 0;
}

void Food::render()
{
	if(!consumed) sprite->render();
}

void Food::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Food::reset()
{
	// random type using time seed
	auto currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

	// Inicializa la semilla srand con el valor de la marca de tiempo
	srand(static_cast<unsigned int>(timestamp));
	type = FoodType(rand() % 28);

	// random number between 10 and 30
	secToAppear = (rand() % 20 + 10)*60;

	consumed = true;
	animationAssigned = false;
	timeCounter = 0;
	blinking = false;

	sprite->changeAnimation(28);
	
	posFood = glm::ivec2(rand()%300+30, 7);
}




