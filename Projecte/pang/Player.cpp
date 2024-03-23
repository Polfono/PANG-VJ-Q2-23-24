#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include "Constants.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT_LEFT, SHOOT_RIGHT, DEAD_LEFT, DEAD_RIGHT, CLIMB1, CLIMB2, CLIMB3, CLIMB4
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheetEscudo.loadFromFile("images/escudo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	escudo = Sprite::createSprite(glm::ivec2(32, 40), glm::vec2(0.5, 1), &spritesheetEscudo, &shaderProgram);
	escudo->setNumberAnimations(1);
	escudo->setAnimationSpeed(0, 12);
	escudo->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	escudo->addKeyframe(0, glm::vec2(0.5f, 0.0f));
	escudo->changeAnimation(0);


	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(30, 32), glm::vec2(0.1, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(13);
		
		sprite->setAnimationSpeed(STAND_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.5f));

		sprite->setAnimationSpeed(STAND_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.3f, 0.5f));

		sprite->setAnimationSpeed(SHOOT_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(SHOOT_RIGHT, glm::vec2(0.1f, 0.5f));

		sprite->setAnimationSpeed(SHOOT_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(SHOOT_LEFT, glm::vec2(0.2f, 0.5f));

		sprite->setAnimationSpeed(DEAD_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(DEAD_LEFT, glm::vec2(0.0f, 0.75f));

		sprite->setAnimationSpeed(DEAD_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(DEAD_RIGHT, glm::vec2(0.1f, 0.75f));

		sprite->setAnimationSpeed(CLIMB1, SPRITE_SPEED);
		sprite->addKeyframe(CLIMB1, glm::vec2(0.0f, 0.25f));

		sprite->setAnimationSpeed(CLIMB2, SPRITE_SPEED);
		sprite->addKeyframe(CLIMB2, glm::vec2(0.2f, 0.25f));

		sprite->setAnimationSpeed(CLIMB3, SPRITE_SPEED);
		sprite->addKeyframe(CLIMB3, glm::vec2(0.1f, 0.25f));

		sprite->setAnimationSpeed(CLIMB4, SPRITE_SPEED);
		sprite->addKeyframe(CLIMB4, glm::vec2(0.2f, 0.25f));

		
		sprite->setAnimationSpeed(MOVE_LEFT, SPRITE_SPEED);
		for (int i = 0; i < 5; i++)
			sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.9f - i*0.1f, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, SPRITE_SPEED);
		for (int i = 0; i < 5; i++)
			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f + i * 0.1f, 0.0f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
	arpon.init(tileMapPos, shaderProgram);
}

bool Player::update(int deltaTime)
{
	escudo->update(deltaTime);
	sprite->update(deltaTime);

	// Comprueba colisiones con las bolas
	if(!god && !BallManager::instance()->isFreezed()) {
		for (Ball* ball : BallManager::instance()->getBalls()) {
			if (checkCollision(ball)) {
				arpon.reset();
				if (!escudoActivo) return true;
				else {
					if (!hitEscudo) {
						ball->split();
						SoundManager::instance().getSoundEngine()->play2D("sounds/shieldBreak.wav", GL_FALSE);
					} 
					hitEscudo = true;
				}
				break;
			}
		}
	}
	
	static bool wasUPpressed = false;
	static bool wasDOWNpressed = false;
	if(!wasUPpressed && !wasDOWNpressed) delayClimb = false;
	wasUPpressed = Game::instance().getKey(GLFW_KEY_UP);
	wasDOWNpressed = Game::instance().getKey(GLFW_KEY_DOWN);

	int posLadder;
	if (!delayClimb && map->inLadder(glm::ivec2(posPlayer.x, posPlayer.y-1), glm::ivec2(30, 34), &posLadder)) // ESTAS EN ESCALERA
	{
		if (Game::instance().getKey(GLFW_KEY_UP)) // QUIERES SUBIR
		{
			sprite->changeAnimation(8 + (posPlayer.y / 10) % 4);
			posPlayer.y -= 2;
			subiendo = true;
			if (!map->inLadder(glm::ivec2(posPlayer.x, posPlayer.y), glm::ivec2(30, 32), &posLadder)) { // ACABAS DE SUBIR
				delayClimb = true;
				subiendo = false;
				if (lastDir) sprite->changeAnimation(STAND_RIGHT);
				else sprite->changeAnimation(STAND_LEFT);
			} // ACABAS DE SUBIR POR AIRE
			else if (map->onlyAir(glm::ivec2(posPlayer.x + 10, posPlayer.y + 16), glm::ivec2(1, 16))) {
				delayClimb = true;
				subiendo = false;
				if (lastDir) sprite->changeAnimation(STAND_RIGHT);
				else sprite->changeAnimation(STAND_LEFT);
			}
			else {
				posPlayer.x = posLadder - 4;
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_DOWN)) // QUIERES BAJAR
		{
			sprite->changeAnimation(8 + (posPlayer.y / 10) % 4);
			posPlayer.y += 2;
			subiendo = true;
			// ACABAS DE BAJAR
			if (map->collisionMoveDownLadder(glm::ivec2(posPlayer.x + 14, posPlayer.y), glm::ivec2(2, 32), &posPlayer.y))
			{
				if (lastDir) sprite->changeAnimation(STAND_RIGHT);
				else sprite->changeAnimation(STAND_LEFT);
				delayClimb = true;
				posPlayer.y -= 2;
				subiendo = false;
			} // DEJAS DE ESTAR EN UNA ESCALERA
			else if (!map->inLadder(glm::ivec2(posPlayer.x, posPlayer.y -1), glm::ivec2(30, 34), &posLadder)) {
				subiendo = false;
				delayClimb = true;
				if (lastDir) sprite->changeAnimation(STAND_RIGHT);
				else sprite->changeAnimation(STAND_LEFT);
			}//ACABAS DE BAJAR POR AIRE
			else if (map->onlyAir(glm::ivec2(posPlayer.x + 10, posPlayer.y + 16), glm::ivec2(1, 16))) {
				delayClimb = true;
				subiendo = false;
				if (lastDir) sprite->changeAnimation(STAND_RIGHT);
				else sprite->changeAnimation(STAND_LEFT);
			}
			else {
				posPlayer.x = posLadder - 4;
			}
		}
	}

	// Si no esta en una escalera se puede caer
	int aux = 0; int* temp = &aux;
	if (!subiendo) {
		speed += 0.2f;
		if (speed > MAX_GRAVITY_SPEED) // MAX_GRAVITY_SPEED
			speed = MAX_GRAVITY_SPEED;
		posPlayer.y += int(round(speed));
		temp = &posPlayer.y;
	}

	// Si esta tocando el suelo y se pulsa por primera vez S se dispara y anima
	if (map->collisionMoveDownPlayer(glm::vec2(posPlayer.x + 5, posPlayer.y), glm::ivec2(20, 32), temp)) {
		speed = 0;
		if (map->playerOverIce())
			overIce = true;
		else
			overIce = false;
		static bool wasSPressed = false;
		if (!wasSPressed && Game::instance().getKey(GLFW_KEY_S) && arpon.setPosition(glm::vec2(posPlayer.x, posPlayer.y))) {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
				sprite->changeAnimation(SHOOT_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
				sprite->changeAnimation(SHOOT_RIGHT);

			SoundManager::instance().getSoundEngine()->play2D("sounds/shoot.mp3", GL_FALSE);
			delayShoot = 5;
			arpon.disparar();
		}
		wasSPressed = Game::instance().getKey(GLFW_KEY_S);
	}

	// Si esta en hielo
	if (overIce) {
		posPlayer.x += round(horizontalSpeed);
		if (horizontalSpeed > 0)
			horizontalSpeed -= 0.2;
		else if (horizontalSpeed < 0)
			horizontalSpeed += 0.2;
	}

	// Si acaba de disparar, se puede mover
	if (!subiendo && --delayShoot < 0)
	{
		if (Game::instance().getKey(GLFW_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);

			lastDir = true;

			if (overIce) {
				horizontalSpeed += 0.3;
				if (horizontalSpeed > 2)
					horizontalSpeed = 2;
			}
			else {
				posPlayer.x += 2;
			}
			
			if (map->collisionMoveRight(posPlayer, glm::ivec2(27, 32)))
			{
				if (overIce)
					horizontalSpeed = 0;
				else 
					posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (Game::instance().getKey(GLFW_KEY_LEFT))
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);

			if (overIce) {
				horizontalSpeed -= 0.3;
				if (horizontalSpeed < -2)
					horizontalSpeed = -2;
			}
			else {
				posPlayer.x -= 2;
			}
		
			lastDir = false;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(30, 32)))
			{
				if (overIce)
					horizontalSpeed = 0;
				else
					posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
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
		speed = -4.5f;
		if (posPlayer.x > 180) dDead = -1;
		else dDead = 1;
	}
	if (--delayDead < 0)
	{
		if (delayDead == -1) SoundManager::instance().getSoundEngine()->play2D("sounds/Hit.mp3", GL_FALSE);
		if(dDead == -1) sprite->changeAnimation(DEAD_LEFT);
		else sprite->changeAnimation(DEAD_RIGHT);

		speed += GRAVEDAD * 1.8f;
		posPlayer.y += int(round(speed));


		// Si toca el suelo, rebota
		if (fBounceDead && map->collisionMoveDownPlayer(posPlayer, glm::ivec2(30, 32), &posPlayer.y))
		{
			speed = -3.0f;
			fBounceDead = false;
		}

		if (fBounceDead && map->collisionMoveUp(posPlayer, glm::ivec2(30, 32), &posPlayer.y))
		{
			speed = -speed;
			fBounceDead = false;
		}

		posPlayer.x += dDead;

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
}

void Player::render()
{
	if (escudoActivo) {
		escudo->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x -1), float(tileMapDispl.y + posPlayer.y -3)));
		if (hitEscudo) {
			--timerEscudo;
			if (timerEscudo / 10 % 2 == 0) escudo->render();
			if (timerEscudo == 0) {
				escudoActivo = false;
				hitEscudo = false;
			}
		}
		else 
			escudo->render();
	}

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

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

bool Player::checkCollision(Ball* ball) {
	glm::ivec2 playerSize = glm::ivec2(30, 32);
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
	speed = 0;
	lastDir = false;
	arpon.reset();
	fDead = true;
	fBounceDead = true;
	subiendo = false;
	escudoActivo = false;
	sprite->changeAnimation(0);
}

void Player::godMode() {
	god = !god;
}

void Player::invincibility() {
	escudoActivo = true;
	hitEscudo = false;
	timerEscudo = 40;
}



