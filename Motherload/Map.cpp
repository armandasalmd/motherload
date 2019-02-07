#include "Map.h"
#include "TextureManager.h"#include <fstream>
#include <sstream>

Map::Map() {
	// map initialization
	LoadBlockPaths();
	LoadMap("maps/map1.mp");
	//PrintMap(map);
	// ___________

	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = Winfo::block_size;
	src.h = dest.h = Winfo::block_size;
}

Map::~Map() {}

void Map::LoadBlockPaths() {
	std::ifstream fd;
	fd.open(paths_file);
	std::string folder = "";
	std::string extention = "";
	std::string temp;

	if (fd.is_open()) {
		fd >> folder >> folder;
		fd >> extention >> extention;
		while (!fd.eof()) {
			fd >> temp;
			block_paths.push_back(folder + temp + extention);
		}
	}
	fd.close();
	/*for (std::vector<std::string>::iterator it = begin(block_paths); it != end(block_paths); it = next(it))
		std::cout << *it << std::endl;*/
}

void Map::LoadMap(char *path) {
	std::ifstream fd(path);
	if (fd.is_open()) {
		
		std::string line = "";
		int block = 0;
		// Reference: https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
		try {
			while (std::getline(fd, line)) {
				std::stringstream ss;
				ss << line;
				std::vector<int> row = {};
				for (int j = 0; j < WorldInfo::b_world_width; j++) {
					ss >> block;
					row.push_back(block);
				}
				map.push_back(row);
				ss.str(""); // creating string stream
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what();
			std::cout << "\nMap must be: " << WorldInfo::b_world_width << "x" << WorldInfo::b_world_height << std::endl;
		}
		
		// End reference;
		fd.close();
	}
}

void Map::LoadMap() { // generates new world
	map = GenerateMap();
	//PrintMap(map);
}

void Map::SaveMap(char *path) {
	std::ofstream fr;
	fr.open(path);
	if (fr.is_open())
		for (const std::vector<int> &v : map) {
			for (int x : v)
				fr << x << ' ';
			fr << '\n';
		}
	fr.close();
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
					//TextureManager::Draw(water, src, dest);
					break;
				case 2:
					//TextureManager::Draw(grass, src, dest);
					break;
				case 3:
					//TextureManager::Draw(dirt, src, dest);
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

int *Map::GetGridCordinates(int x, int y) {
	int *mArr = new int[2]{ -1, -1 };
	if (Winfo::block_size != 0) {
		mArr[0] = x / Winfo::block_size;
		mArr[1] = y / Winfo::block_size;
	}
	// std::cout << mArr[0] << ", " << mArr[1] << std::endl;
	return mArr;
}