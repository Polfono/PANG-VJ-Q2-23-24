#include "Arpon.h"
#include <iostream>
#include <GL/glew.h>
#include "Arpon.h"
#include "Game.h"
#include "Constants.h"

void Arpon::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bThrowing = false;
	spritesheet.loadFromFile("images/arpon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(9, 200), glm::vec2(0.01454334, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(NUMBER_FRAMES_ARPON);

	sprite->setAnimationSpeed(0, SPRITE_SPEED);
	for (int i = 0; i < NUMBER_FRAMES_ARPON; i++)
		sprite->addKeyframe(i, glm::vec2(0.0145 * i, 0.0f));
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posArpon.x), float(tileMapDispl.y + posArpon.y)));
}

void Arpon::update()
{
	static bool wasSPressed = false;

	if (Game::instance().getKey(GLFW_KEY_S) && !wasSPressed) {  // S is newly pressed
		bThrowing = true;  // Toggle throwing state
	}

	wasSPressed = Game::instance().getKey(GLFW_KEY_S);

	if (bThrowing) {
		altura += 2;
		sprite->changeAnimation(sprite->animation() + 1);

		if (map->pointCollision(glm::vec2(posArpon.x, posArpon.y + 155 - altura), glm::ivec2(9, 9)) || altura == 138) {
			bThrowing = false;
			altura = 0;
			sprite->changeAnimation(0);
		}
		else {
			for (Ball* ball : BallManager::instance()->getBalls()) {
				if (checkCollision(ball)) {
					bThrowing = false;
					altura = 0;
					sprite->changeAnimation(0);

					ball->split();
					break;
				}
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posArpon.x), float(tileMapDispl.y + posArpon.y)));
}

void Arpon::render()
{
	if (bThrowing) {
		sprite->render();
	}
}

void Arpon::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

bool Arpon::setPosition(const glm::vec2& pos)
{
	if (!bThrowing) {
		posArpon = glm::vec2(pos.x +12, pos.y -168);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posArpon.x), float(tileMapDispl.y + posArpon.y)));
		return true;
	}
	return false;
}

bool Arpon::checkCollision(Ball* ball) {
	glm::ivec2 arponSize = glm::ivec2(9, 34 + altura);
	glm::ivec2 ballSize = ball->getSize();
	glm::vec2 arponPos = glm::vec2(posArpon.x+30, posArpon.y + 175 - altura);
	glm::vec2 ballPos = ball->getPosition();

	if (arponPos.x < ballPos.x + ballSize.x &&
		arponPos.x + arponSize.x > ballPos.x &&
		arponPos.y < ballPos.y + ballSize.y &&
		arponSize.y + arponPos.y > ballPos.y) {
		return true;
	}
	return false;
}
