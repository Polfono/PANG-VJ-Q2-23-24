#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Ball.h"
#include "Game.h"
#include <map>
#include "Constants.h"
#include <cmath>
#include "BallManager.h"



// tamaño de la bola, tamaño de la bola en el spritesheet, posición en el spritesheet, velocidad

std::map<BallSize, std::tuple<glm::ivec2, glm::vec2, float, float>> sizeMap = {
    {SMALL, {glm::ivec2(5, 5), glm::vec2(0.0375, 0.041666), 0.74f, 2.75f}},
    {MEDIUM, {glm::ivec2(10, 10), glm::vec2(0.07083, 0.078125), 0.49f, 3.375f}},
    {LARGE, {glm::ivec2(20, 20), glm::vec2(0.1375, 0.140625), 0.24f, 4.0f}},
    {EXTRA_LARGE, {glm::ivec2(40, 40), glm::vec2(0.2, 0.21354), 0.0f, 4.625f}}
};

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, BallSize size, int dir)
{
    this->size = size;
	speed = -1.0f;
	direction = dir;
	spritesheet.loadFromFile("images/balloons.png", TEXTURE_PIXEL_FORMAT_RGBA);

    sprite = Sprite::createSprite(get<0>(sizeMap[size]), get<1>(sizeMap[size]), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(5);

    sprite->setAnimationSpeed(0, SPRITE_SPEED);
    for(int i = 0; i < 5; i++)
		sprite->addKeyframe(i, glm::vec2(i * 0.2f, get<2>(sizeMap[size])));
    sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

void Ball::update()
{
    if (destroyCounter <= 0) {
        speed += GRAVEDAD;
        posBall.y += int(round(speed));

    // Techo
        if (map->collisionMoveUp(posBall, get<0>(sizeMap[size]), &posBall.y))
        {
            posBall.y -= int(round(speed));
            speed = -speed;
        }

        // Suelo
        if (map->collisionMoveDownBall(posBall, get<0>(sizeMap[size]), &posBall.y))
        {
            speed = max(-get<3>(sizeMap[size]), -sqrt(2 * GRAVEDAD * (posBall.y - 15))); // 15 es la altura maxima
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
    else
    {
        destroyCounter--;
        if (destroyCounter == 0) BallManager::instance()->removeBall(this);
		else if (destroyCounter == 15) sprite->changeAnimation(2);
        else if (destroyCounter == 10) sprite->changeAnimation(3);
        else if (destroyCounter == 5) sprite->changeAnimation(4);
    }
}

void Ball::split()
{
    BallManager* ballManager = BallManager::instance();

    if (size != 0)
    {
        BallSize newSize = BallSize(int(size) - 1);
        int aux = get<0>(sizeMap[newSize])[0];
        ballManager->addBall(glm::vec2(posBall.x + aux, posBall.y + aux/2), tileMapDispl, newSize, 1);
        ballManager->addBall(glm::vec2(posBall.x, posBall.y + aux/2), tileMapDispl, newSize, -1);
    }

    SoundManager::instance().getSoundEngine()->play2D("sounds/pop.mp3", GL_FALSE);

    //probablididad de que salga un powerup 0.1
    srand(time(NULL));
    if (rand() % 9 == 0) PowerupsManager::instance()->addPowerup(glm::vec2(posBall.x, posBall.y), tileMapDispl);

    destroyCounter = 20;
    sprite->changeAnimation(1);
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

bool Ball::isDestroyed()
{
	return destroyCounter > 0;
}