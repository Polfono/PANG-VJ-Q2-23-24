#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include "Constants.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT_LEFT, SHOOT_RIGHT, DEAD_LEFT, DEAD_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.08, 0.16), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
		
		sprite->setAnimationSpeed(STAND_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.025f, 0.53f));

		sprite->setAnimationSpeed(STAND_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.89f, 0.53f));

		sprite->setAnimationSpeed(SHOOT_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.025f + 0.086f, 0.53f));

		sprite->setAnimationSpeed(SHOOT_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.89f - 0.086f, 0.53f));

		sprite->setAnimationSpeed(DEAD_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(DEAD_LEFT, glm::vec2(0.025f + 2*0.086f, 0.53f));

		sprite->setAnimationSpeed(DEAD_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(DEAD_RIGHT, glm::vec2(0.025f + 0.282f, 0.53f));

		
		sprite->setAnimationSpeed(MOVE_LEFT, SPRITE_SPEED);
		for (int i = 0; i < 5; i++)
			sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.89f - i*0.086f, 0.01f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, SPRITE_SPEED);
		for (int i = 0; i < 5; i++)
			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.025f + i * 0.086f, 0.01f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
	arpon.init(tileMapPos, shaderProgram);
}

bool Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	// Comprueba colisiones con las bolas
	for (Ball* ball : BallManager::instance()->getBalls()) {
		if (checkCollision(ball)) {
			arpon.reset();
			return true;
		}
	}

	posPlayer.y += FALL_STEP;
	// Si esta tocando el suelo y se pulsa por primera vez S se dispara y anima
	static bool wasSPressed = false;
	if (map->collisionMoveDownPlayer(posPlayer, glm::ivec2(32, 32), &posPlayer.y) && !wasSPressed && Game::instance().getKey(GLFW_KEY_S) && arpon.setPosition(glm::vec2(posPlayer.x, posPlayer.y))) {
		if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
			sprite->changeAnimation(SHOOT_LEFT);
		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
			sprite->changeAnimation(SHOOT_RIGHT);

		delayShoot = 5;
		arpon.disparar();
	}
	wasSPressed = Game::instance().getKey(GLFW_KEY_S);

	// Si acaba de disparar, se puede mover
	if (--delayShoot < 0)
	{
		if (Game::instance().getKey(GLFW_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(27, 32)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == SHOOT_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == SHOOT_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	arpon.update();

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	return false;
}

void Player::die()
{
	if (fDead)
	{
		delayDead = 30;
		fDead = false;
		if (posPlayer.x > 180) dDead = -1;
		else dDead = 1;
	}
	if (--delayDead < 0)
	{
		if(dDead == -1) sprite->changeAnimation(DEAD_LEFT);
		else sprite->changeAnimation(DEAD_RIGHT);

		speed += GRAVEDAD * 1.8f;
		posPlayer.y += int(round(speed));


		// Si toca el suelo, rebota
		if (fBounceDead && map->collisionMoveDownPlayer(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			speed = -3.0f;
			fBounceDead = false;
		}

		posPlayer.x += dDead;

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
}

void Player::render()
{
	arpon.render();
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
	arpon.setTileMap(tileMap);
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Player::checkCollision(Ball* ball) {
	glm::ivec2 playerSize = glm::ivec2(32, 32);
	glm::vec2 playerPos = glm::vec2(posPlayer.x + 48, posPlayer.y +26);
	float ballRadius = ball->getSize()[1]/2;
	glm::vec2 ballPos = ball->getPosition();
	ballPos = glm::vec2(ballPos.x + ballRadius, ballPos.y + ballRadius);

	// Calcula la distancia entre el centro del jugador y el centro de la bola
	float distX = playerPos.x - ballPos.x;
	float distY = playerPos.y - ballPos.y;

	float distance = sqrt((distX * distX) + (distY * distY));

	// Si la distancia es menor que el radio de la bola, hay una colisión
	if (distance < ballRadius + 8) {
		return true;
	}
	return false;
}

void Player::reset() {
	fDead = true;
	fBounceDead = true;
	speed = -4.5f;
	sprite->changeAnimation(0);
}




