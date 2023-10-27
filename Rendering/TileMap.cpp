#include "TileMap.h"

std::vector<TileMap*> TileMap::tileMaps;

TileMap::TileMap(int width, int height, int tileSize, std::string mapPath)
{
	tileMaps.push_back(this);

	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->numTiles = width * height;

	tiles.resize(width);
	for (int i = 0; i < width; i++)
	{
		tiles[i].resize(height);
	}
	LoadMapFromFile(mapPath);
}

TileMap::~TileMap()
{
	tiles.clear();
}

void TileMap::LoadMapFromFile(std::string mapPath)
{
	std::ifstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		// load the file to the map
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				std::string tileID;
				mapFile >> tileID;
				tiles[i][j] = tileID;
			}
		}
		mapFile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void TileMap::SaveMaptoFile(std::string mapPath)
{
	std::ofstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				mapFile << tiles[i][j] << " ";
			}
			mapFile << std::endl;
		}
		mapFile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

std::pair<float, float> TileMap::GetTilePositionById(std::string id)
{
	std::pair<float, float> result(0, 0);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (tiles[i][j] == id)
			{
				result.first = i * tileSize;
				result.second = j * tileSize;
				return result;
			}
		}
	}
	return result;
}

void TileMap::Clear()
{
	for (int i = 0; i < tileMaps.size(); i++)
	{
		delete tileMaps[i];
		tileMaps[i] = nullptr;
	}
	tileMaps.clear();
}

