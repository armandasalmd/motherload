#include "Map.h"
#include "TextureManager.h"

Map::Map() {
	water = TextureManager::LoadTexture("assets/water.png"); // 1
	grass = TextureManager::LoadTexture("assets/grass.png"); // 2
	dirt = TextureManager::LoadTexture("assets/dirt.png"); // 3

	LoadMap();	

	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = Winfo::block_size;
	src.h = dest.h = Winfo::block_size;
}

Map::~Map()
{
}

void Map::LoadMap(std::vector<std::vector<int>> m_map) {
	map = m_map;
}

void Map::LoadMap() { // generates new world
	map = GenerateMap();
	//PrintMap(map);
}

void Map::DrawMap()
{
	int type = 0; // block id
	for (int y = 0; y < Winfo::blocks_y; y++) // row
		for (int x = 0; x < Winfo::blocks_x; x++) // column
		{
			type = map[y][x];
			dest.x = x * Winfo::block_size;
			dest.y = y * Winfo::block_size;

			switch (type) {
				case 1:
					TextureManager::Draw(water, src, dest);
					break;
				case 2:
					TextureManager::Draw(grass, src, dest);
					break;
				case 3:
					TextureManager::Draw(dirt, src, dest);
					break;
				default:
					break;
			}
		}
}

void Map::PrintMap(std::vector<std::vector<int>> m_map) {
	for (const std::vector<int> &v : m_map)
	{
		for (int x : v)
			std::cout << x << ' ';
		std::cout << std::endl;
	}
}

std::vector<std::vector<int>> Map::GenerateMap() {
	std::vector<std::vector<int>> new_map(Winfo::blocks_y, std::vector<int>(Winfo::blocks_x)); // [row][column]

	for (int y = 0; y < 4; y++) // sky layer
		for (int x = 0; x < Winfo::blocks_x; x++)
			new_map[y][x] = 1; // [y-row][x-column]

	for (int x = 0; x < Winfo::blocks_x; x++) // grass layer
		new_map[4][x] = 2;

	for (int y = 5; y < Winfo::blocks_y; y++) // dirt layer
		for (int x = 0; x < Winfo::blocks_x; x++)
			new_map[y][x] = 3;

	return new_map;
}