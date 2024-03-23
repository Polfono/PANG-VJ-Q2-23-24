#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <vector>

using namespace std;


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDownBall(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveDownPlayer(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveDownLadder(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool pointCollision(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool tileInRegion(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool inLadder(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) const;
	bool onlyAir(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool checkBrokenBlocks();
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);
	void doAnimations();
	bool playerOverIce();

private:
	bool loadLevel(const string &levelFile);
	int colorOfBlock(int block) const;
	bool isAnimationBlock(int block) const;
	

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;
	mutable bool overIce = false;
	vector<int> destroyableBlocks = {5, 25, 26, 27, 28, 60, 61, 62, 65, 66, 67, 70, 71, 72, 73, 74, 81, 82, 83, 84, 89, 90, 91, 92};
	vector<int> blueBlocksId = {65, 66, 67};
	vector<int> goldBlocksId = {5, 25, 26, 27, 28, 70, 71, 72, 73, 74, 81, 82, 83, 84};
	vector<int> pinkBlocksId = {60, 61, 62, 89, 90, 91, 92};
	vector<int> animationBlocks = { 77, 78, 79, 80, 85, 86, 87, 88, 93, 94, 95, 96};
	mutable bool brokenBlocks = false;
	mutable vector<pair<int, pair<int,int>>> blueBlocks; // (blockId (timeLeftAnimation, numberAnimation)
	mutable vector<pair<int, pair<int,int>>> goldBlocks;
	mutable vector<pair<int, pair<int,int>>> pinkBlocks;
};


#endif // _TILE_MAP_INCLUDE


