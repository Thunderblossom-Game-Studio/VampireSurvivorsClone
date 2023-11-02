#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Tile.h"

class TileMap
{
private:

	static std::vector<TileMap*> tileMaps;

protected:

	Uint8 width;
	Uint8 height;
	float tileSize;
	int numTiles;

	std::vector<std::vector<Tile*>> tiles;

public:
	TileMap(int width, int height, int tileSize, std::string mapPath);
	~TileMap();

	void LoadMap(std::string mapPath);
	virtual void DrawMap() {};
	void SaveMaptoFile(std::string mapPath = "Assets/Maps/Map1.txt");

	std::pair<float, float> GetTilePositionById(std::string id);

	static void Clear();
};
