#include "BallManager.h"
#include <iostream>
#include "ShaderProgramManager.h"

BallManager* BallManager::s_inst = nullptr;

void BallManager::addBall(const glm::vec2& pos, const glm::ivec2& tileMapPos, BallSize size, int dir)
{
	Ball* ball = new Ball();
	ball->init(tileMapPos, ShaderProgramManager::instance().getShaderProgram(), size, dir);
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

bool BallManager::updateBalls()
{
	if(balls.empty())
		return false;

	for (auto& ball : balls)
	{
		ball->update();
	}
	return true;
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

vector<Ball*> BallManager::getBalls()
{
	// return all non splited balls
	vector<Ball*> nonSplitedBalls;
	for (auto& ball : balls)
	{
		if (!ball->isDestroyed())
		{
			nonSplitedBalls.push_back(ball);
		}
	}
	return nonSplitedBalls;
}

void BallManager::clearBalls() {
	for (auto& ball : balls)
	{
		delete ball;
	}
	balls.clear();
}

