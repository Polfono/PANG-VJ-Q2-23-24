#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include "Constants.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.08, 0.16), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
		
		sprite->setAnimationSpeed(STAND_RIGHT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.025f, 0.53f));

		sprite->setAnimationSpeed(STAND_LEFT, SPRITE_SPEED);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.89f, 0.53f));

		
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

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (Game::instance().getKey(GLFW_KEY_S)) arpon.setPosition(glm::vec2(posPlayer.x, posPlayer.y));
	arpon.update();

	if(Game::instance().getKey(GLFW_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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




