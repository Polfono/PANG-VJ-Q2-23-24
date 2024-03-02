#include "BallManager.h"
#include <iostream>

BallManager* BallManager::s_inst = nullptr;

void BallManager::addBall(const glm::vec2& pos, const glm::ivec2& tileMapPos, BallSize size, int dir)
{
	Ball* ball = new Ball();
	ball->init(tileMapPos, texProgram, size, dir);
	ball->setPosition(pos);
	ball->setTileMap(map);
	balls.push_back(ball);
}

void BallManager::removeBall(Ball* ball)
{
	for (auto it = balls.begin(); it != balls.end(); ++it)
	{
		if (*it == ball)
		{
			balls.erase(it);
			delete ball;
			break;
		}
	}
}

void BallManager::updateBalls()
{
	for (auto& ball : balls)
	{
		ball->update();
	}
}

void BallManager::renderBalls()
{
	for (auto& ball : balls)
	{
		ball->render();
	}
}

void BallManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BallManager::setShaderProgram(ShaderProgram& shaderProgram)
{
	texProgram = shaderProgram;
}

vector<Ball*> BallManager::getBalls()
{
	return balls;
}

