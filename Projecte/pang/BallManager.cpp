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
	if (balls.empty())
		return false;

	--delayFreeze;
	if (delayFreeze == 0) {
		freezed = false;
		delayFreeze = 0;
	}	

	// si aun hay bolas no small
	--delayDynamite;
	if (delayDynamite == 0) {
		vector<Ball*> nonSplitedBalls = getBalls();
		for (auto& ball : nonSplitedBalls)
		{
			if (!ball->isSmall())
			{
				dynamite();
			}
		}
	}

	--delaySlow;
	if (delaySlow < 0 || delaySlow % 3 > 0) {
		for (auto& ball : balls)
		{
			ball->update();
		}
	}
	return true;
}

void BallManager::renderBalls()
{	
	if (delayFreeze < 1 || (delayFreeze > 10 && delayFreeze < 20) || (delayFreeze > 30 && delayFreeze < 40) || (delayFreeze > 50 && delayFreeze < 60) || (delayFreeze > 70 && delayFreeze < 80) || (delayFreeze > 90 && delayFreeze < 100) || delayFreeze > 110)
	{
		for (auto& ball : balls)
		{
			ball->render();
		}
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
	freezed = false;
	delayDynamite = 0;
	delayFreeze = 0;
	delaySlow = 0;
	for (auto& ball : balls)
	{
		delete ball;
	}
	balls.clear();
}

// for all non small balls split
void BallManager::dynamite()
{
	vector<Ball*> nonSplitedBalls = getBalls();
	for (auto& ball : nonSplitedBalls)
	{
		if (!ball->isSmall())
		{
			ball->split();
		}
	}

	delayDynamite = 20;
}

void BallManager::freezeTime()
{
	delayFreeze = 60 * 5;
	freezed = true;
}

bool BallManager::isFreezed()
{
	return freezed;
}

void BallManager::slowTime()
{
	delaySlow = 60 * 5;
}