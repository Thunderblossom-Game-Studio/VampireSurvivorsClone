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
	LoadMap(mapPath);
}

TileMap::~TileMap()
{
	for (std::vector<Tile*> tileRows : tiles)
	{
		for (Tile* tile : tileRows)
		{
			if (tile)
				delete tile;
		}
	}
	tiles.clear();
}

void TileMap::LoadMap(std::string mapPath)
{
	for (std::vector<Tile*> tileRows : tiles)
	{
		for (Tile* tile : tileRows)
		{
			if (tile)
				delete tile;
		}
		tileRows.clear();
	}
	tiles.clear();

	std::ifstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		//// load the file to the map
		//for (int i = 0; i < width; i++)
		//{
		//	for (int j = 0; j < height; j++)
		//	{
		//		std::string tileID;
		//		mapFile >> tileID;
		//		std::cout << tileID;
		//	}
		//	std::cout << std::endl;
		//}

		std::string lineText;
		int i = height - 1;
		while (std::getline(mapFile, lineText))
		{
			std::vector<Tile*> tileRow;
			for (int j = 0; j < lineText.length(); ++j)
			{
				Vector2 pos = { (j * tileSize) - (width * tileSize)/2, (i * tileSize) - (height * tileSize) / 2 };
				switch (lineText[j])
				{
				case 'F':
				{
					tileRow.push_back(new Tile(
						pos,
						{ tileSize,tileSize },
						"Assets/Textures/TextureLoadingTest.png",
						{ 16,64,16,16 },
						-5,
						NONE
					));
					break;
				}
				case 'B':
				{
					tileRow.push_back(new Tile(
						pos,
						{ tileSize,tileSize },
						"Assets/Textures/TextureLoadingTest.png",
						{ 32,64,16,16 },
						-5,
						NONE
					));
					break;
				}
				case 'Q':
				{
					tileRow.push_back(new Tile(
						pos,
						{ tileSize,tileSize },
						"Assets/Textures/TextureLoadingTest.png",
						{ 16,12,16,16 },
						0,
						RECTANGLE
					));
					break;
				}
				case 'W':
				{
					tileRow.push_back(new Tile(
						pos,
						{ tileSize,tileSize },
						"Assets/Textures/TextureLoadingTest.png",
						{ 32,12,16,16 },
						0,
						RECTANGLE
					));
					break;
				}
				case 'E':
				{
					tileRow.push_back(new Tile(
						pos,
						{ tileSize,tileSize },
						"Assets/Textures/TextureLoadingTest.png",
						{ 48,12,16,16 },
						0,
						RECTANGLE
					));
					break;
				}
				}
			}
			tiles.push_back(tileRow);
			--i;
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
			//if (tiles[i][j] == id)
			//{
			//	result.first = i * tileSize;
			//	result.second = j * tileSize;
			//	return result;
			//}
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

