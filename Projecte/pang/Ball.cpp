#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Ball.h"
#include "Game.h"
#include <map>
#include "Constants.h"



// tama�o de la bola, tama�o de la bola en el spritesheet, posici�n en el spritesheet, velocidad

std::map<BallSize, std::tuple<glm::ivec2, glm::vec2, glm::vec2, float>> sizeMap = {
    {SMALL, {glm::ivec2(8, 8), glm::vec2(0.06, 0.05), glm::vec2(0.87, 0.12), 2.75f}},
    {MEDIUM, {glm::ivec2(14, 14), glm::vec2(0.13, 0.1), glm::vec2(0.7, 0.1), 3.375f}},
    {LARGE, {glm::ivec2(26, 26), glm::vec2(0.26, 0.186), glm::vec2(0.425, 0.05), 4.0f}},
    {EXTRA_LARGE, {glm::ivec2(40, 40), glm::vec2(0.4, 0.2857), glm::vec2(0.0, 0.0), 4.625f}}
};

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, BallSize size, int dir)
{
    this->size = size;
	speed = -1.0f;
	direction = dir;
	spritesheet.loadFromFile("images/balloons.png", TEXTURE_PIXEL_FORMAT_RGBA);

    sprite = Sprite::createSprite(get<0>(sizeMap[size]), get<1>(sizeMap[size]), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, SPRITE_SPEED);
    sprite->addKeyframe(0, get<2>(sizeMap[size]));
    sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

void Ball::update()
{
    speed += GRAVEDAD;
    posBall.y += int(round(speed));

    // Techo
    if (map->collisionMoveUp(posBall, get<0>(sizeMap[size]), &posBall.y))
    {
        posBall.y -= int(round(speed));
        speed = -speed;
	}

    // Suelo
    if (map->collisionMoveDown(posBall, get<0>(sizeMap[size]), &posBall.y))
    {
        posBall.y -= int(round(speed));
        if (posBall.y < 55) speed = -1.75;
        else if (posBall.y < 65) speed = -2.8;
        else if (posBall.y < 80) speed = -3.2;
        else if (posBall.y < 95) speed = -3.5;
        else speed = -get<3>(sizeMap[size]);

        // Min speed = -4.625
        // Min posBall = 155
    }

    posBall.x += direction;

    // Paredes
    if (map->collisionMoveLeft(posBall, get<0>(sizeMap[size])) || map->collisionMoveRight(posBall, get<0>(sizeMap[size])))
    {
        posBall.x -= direction;
        direction = -direction;
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

void Ball::split()
{
    BallManager* ballManager = BallManager::instance();

    if (size != 0)
    {
        BallSize newSize = BallSize(int(size) - 1);
        ballManager->addBall(glm::vec2(posBall.x + get<0>(sizeMap[newSize])[0], posBall.y + 5), tileMapDispl, newSize, 1);
        ballManager->addBall(glm::vec2(posBall.x, posBall.y + 5), tileMapDispl, newSize, -1);
    }
	
    ballManager->removeBall(this);
}


void Ball::render()
{
	sprite->render();
}

void Ball::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Ball::setPosition(const glm::vec2& pos)
{
	posBall = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

glm::ivec2 Ball::getSize()
{
	return get<0>(sizeMap[size]);
}

glm::vec2 Ball::getPosition()
{
	return glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y));
}