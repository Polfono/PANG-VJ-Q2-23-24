#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include <queue>


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin >> map[j*mapSize.x + i];
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x) / tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		int block = map[y * mapSize.x + x];
		if(block != 0 && block != 33 && block != 34 && block != 35)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		int block = map[y * mapSize.x + x];
		if (block != 0 && block != 33 && block != 34 && block != 35)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDownBall(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		int block = map[y * mapSize.x + x];
		if (block != 0 && block != 33 && block != 34 && block != 35)
		{
			if(*posY - tileSize * y + size.y <= 8)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

bool TileMap::collisionMoveDownPlayer(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		int block = map[y * mapSize.x + x];
		if (block != 0)
		{
			if (*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveDownLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		int block = map[y * mapSize.x + x];
		if (block != 0 && block != 33 && block != 34 && block != 35 && block != 41 && block != 42 && block != 43 && block != 49 && block != 50 && block != 51)
		{
			if (*posY - tileSize * y + size.y <= 8)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	// Check for collisions in the tiles the box is overlapping
	for (int x = x0; x <= x1; x++)
	{
		int block = map[y * mapSize.x + x];
		// If the tile is not empty, the box is colliding
		if (block != 0 && block != 33 && block != 34 && block != 35 && block != 41 && block != 42 && block != 43 && block != 49 && block != 50 && block != 51)
		{
			// If the box is already intersecting the tile, correct the position
			if (tileSize * (y + 1) - *posY <= 8)
			{
				*posY = tileSize * (y + 1);
				return true;
			}
		}
	}

	return false;
}

bool TileMap::pointCollision(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y0, y1;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		for (int y = y0; y <= y1; y++)
		{
			int block = map[y * mapSize.x + x];

			// Checking if it is a destroyable block 
			for (int i = 0; i < destroyableBlocks.size(); i++)
			{
				if (destroyableBlocks[i] == block)
				{
					// Destroy Blocks  -- Todo lo de aqui no me deja ponerlo en otra funcion :(
					int coord = y * mapSize.x + x;

					queue<pair<int,int>> cola;
					pair<int, int> node = pair<int,int>(coord, block);
					cola.push(node);

					while (!cola.empty()) {
						node = cola.front();
						cola.pop();
						int c = node.first;
						int b = node.second;

						if (map[c] >= b - 1 && map[c] <= b + 1) {
							if (!isAnimationBlock(map[c])) {
								int type = colorOfBlock(b);

								b = map[c];
								if (type == 0) { // Blue
									map[c] = 93;
									blueBlocks.push_back(make_pair(c, make_pair(10, 4)));
								}
								else if (type == 1) { // Gold
									map[c] = 77;
									goldBlocks.push_back(make_pair(c, make_pair(10, 4)));
								}
								else {
									map[c] = 85; // Pink
									blueBlocks.push_back(make_pair(c, make_pair(10, 4)));
								}

								if (map[c - 1] >= b - 1 && map[c - 1] <= b + 1) { // Esquerra
									cola.push(make_pair(c - 1, b));
								}
								if (map[c + 1] >= b - 1 && map[c + 1] <= b + 1) { // Dreta
									cola.push(make_pair(c + 1, b));
								}
								if (c - mapSize.x >= 0 && map[c - mapSize.x] >= b - 1 && map[c - mapSize.x] <= b + 1) {
									cola.push(make_pair(c - mapSize.x, b));  // Up
								}
								if (c + mapSize.x < mapSize.x * mapSize.y && map[c + mapSize.x] >= b - 1 && map[c + mapSize.x] <= b + 1) {
									cola.push(make_pair(c + mapSize.x, b));  // Down
								}
							}
						}
					}
					
					brokenBlocks = true;

					break;
				}
			}

			if (block != 0 && block != 33 && block != 34 && block != 35)
				return true;
		}
	}

	return false;
}	

bool TileMap::inLadder(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const
{
	int x0, x1, y0, y1;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		for (int y = y0; y <= y1; y++)
		{
			int block = map[y * mapSize.x + x];
			if (block == 34 || block == 42 || block == 50)
			{
				*posX = tileSize * (x + 1) - size.x / 2;
				return true;
			}
				
		}
	}

	return false;
}

bool TileMap::onlyAir(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y0, y1;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		for (int y = y0; y <= y1; y++)
		{
			int block = map[y * mapSize.x + x];
			if (block != 0)
			{
				return false;
			}
			// bloque de abajo de aire no es escalera
			int blockBelow = map[(y + 2) * mapSize.x + x];
			if (blockBelow != 33 && blockBelow != 34 && blockBelow != 35 && blockBelow != 41 && blockBelow != 42 && blockBelow != 43 && blockBelow != 49 && blockBelow != 50 && blockBelow != 51)
			{
				return false;
			}
		}
	}

	return true;
}

bool TileMap::checkBrokenBlocks()
{
	return brokenBlocks;
}

void TileMap::doAnimations()
{
	if (!blueBlocks.empty()) {
		for (int i = 0; i < blueBlocks.size(); i++) {
			if (--blueBlocks[i].second.first <= 0) {
				if (--blueBlocks[i].second.second <= 0) {
					map[blueBlocks[i].first] = 0;
					blueBlocks.erase(blueBlocks.begin() + i);
				}
				else {
					map[blueBlocks[i].first]++;
				}
			}
		}
	}
	if (!pinkBlocks.empty()) {
		for (int i = 0; i < pinkBlocks.size(); i++) {
			if (--pinkBlocks[i].second.first <= 0) {
				if (--pinkBlocks[i].second.second <= 0) {
					map[pinkBlocks[i].first] = 0;
					pinkBlocks.erase(pinkBlocks.begin() + i);
				}
				else {
					map[pinkBlocks[i].first]++;
				}
			}
		}
	}
	if (!goldBlocks.empty()) {
		for (int i = 0; i < goldBlocks.size(); i++) {
			if (--goldBlocks[i].second.first <= 0) {
				if (--goldBlocks[i].second.second <= 0) {
					map[goldBlocks[i].first] = 0;
					goldBlocks.erase(goldBlocks.begin() + i);
				}
				else {
					map[goldBlocks[i].first]++;
				}
			}
		}
	}
}

int TileMap::colorOfBlock(int block) const
{
	for (int i = 0; i < blueBlocksId.size(); i++) {
		if (block == blueBlocksId[i])
			return 0;
	}
	for (int i = 0; i < goldBlocksId.size(); i++) {
		if (block == goldBlocksId[i])
			return 1;
	}
	for (int i = 0; i < pinkBlocksId.size(); i++) {
		if (block == pinkBlocksId[i])
			return 2;
	}
	return -1;
}

bool TileMap::isAnimationBlock(int block) const
{
	for (int i = 0; i < animationBlocks.size(); i++)
	{
		if (block == animationBlocks[i])
			return true;
	}
	return false;
}

