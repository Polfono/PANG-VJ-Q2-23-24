#ifndef _BALLMANAGER_INCLUDE
#define _BALLMANAGER_INCLUDE

#include <vector>
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
	void updateBalls();
	void renderBalls();
	void splitAll();
	vector<Ball*> getBalls();

	void setTileMap(TileMap* tileMap);
	void setShaderProgram(ShaderProgram& shaderProgram);

private:
	BallManager() {}
	static BallManager* s_inst;
	vector<Ball*> balls;
	ShaderProgram texProgram;
	TileMap* map;
};

#endif
