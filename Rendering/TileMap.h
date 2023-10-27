#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TileMap
{
private:

	static std::vector<TileMap*> tileMaps;

protected:

	int width;
	int height;
	int tileSize;
	int numTiles;

	std::vector<std::vector<std::string>> tiles;

public:
	TileMap(int width, int height, int tileSize, std::string mapPath);
	~TileMap();

	void LoadMapFromFile(std::string mapPath);
	virtual void DrawMap() {};
	void SaveMaptoFile(std::string mapPath = "Assets/Maps/Map1.txt");

	std::pair<float, float> GetTilePositionById(std::string id);

	static void Clear();
};
