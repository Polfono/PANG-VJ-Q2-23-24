
#ifndef _BALLMANAGER_INCLUDE
#define _BALLMANAGER_INCLUDE

#include <vector>
#include <stack>
#include "Ball.h"

class BallManager
{

public:
	static BallManager* instance()
	{
		if (s_inst == nullptr)
		{
			s_inst = new BallManager();
		}
		return s_inst;
	}
	void addBall(const glm::vec2& pos, const glm::ivec2& tileMapPos, BallSize size, int dir);
	void removeBall(Ball* ball);
	bool updateBalls();
	void renderBalls();
	vector<Ball*> getBalls();
	void clearBalls();
	void dynamite();
	void freezeTime();
	bool isFreezed();
	void slowTime();
	void addScore(int size, glm::vec2 pos);

	void setTileMap(TileMap* tileMap);

private:
	BallManager() {}
	static BallManager* s_inst;
	vector<Ball*> balls;
	TileMap* map;
	stack <int> lastBalls = stack<int>();
	int delayDynamite = 0;
	int delayFreeze = 0;
	bool freezed = false;
	int delaySlow = 0;
};

#endif
