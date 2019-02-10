#pragma once
#include "Map.h"


Map::Map(Player *player) {
	this->player = player;
	water = TextureManager::LoadTexture("assets/water.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	stone = TextureManager::LoadTexture("assets/stone.png");
	bronze = TextureManager::LoadTexture("assets/bronzium.png");
	silver = TextureManager::LoadTexture("assets/silverium.png");
	iron = TextureManager::LoadTexture("assets/ironium.png");
	gold = TextureManager::LoadTexture("assets/goldium.png");
	ruby = TextureManager::LoadTexture("assets/ruby.png");
	emerald = TextureManager::LoadTexture("assets/emerald.png");
	diamond = TextureManager::LoadTexture("assets/diamond.png");

	//Map initialization
	//LoadBlockPaths();
	LoadMap();
	//LoadMap("maps/map1.mp");
	PrintMap(matrix);
	// ___________

	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = Winfo::block_size;
	src.h = dest.h = Winfo::block_size;
}

Map::~Map() {}
/*
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
	*/
	/*for (std::vector<std::string>::iterator it = begin(block_paths); it != end(block_paths); it = next(it))
		std::cout << *it << std::endl;*/
//}

/*
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
*/
	

void Map::LoadMap() { // generates new world
	this->matrix = GenerateMap();
	//PrintMap(map);
}
/*
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
*/

void Map::DrawMap(int camX, int camY)
{
	int camXCoords = camX / 64;
	int camYCoords = camY / 64;
	int xEdge;
	int yEdge;
	bool xLimit = WorldInfo::b_world_width - (camXCoords + Winfo::blocks_x + 1) >= 0;
	bool yLimit = WorldInfo::b_world_height - (camYCoords + Winfo::blocks_y + 1) >= 0;

	if (xLimit && yLimit) {
		yEdge = camYCoords + Winfo::blocks_y + 1;
		xEdge = camXCoords + Winfo::blocks_x + 1;
	}
	else{
		yEdge = WorldInfo::b_world_height;
		xEdge = WorldInfo::b_world_width;
	}
	this->render(camXCoords, camYCoords, camX, camY, xEdge, yEdge);
}


void Map::PrintMap(std::vector<std::vector<Material>> m_map) {
	for (const std::vector<Material> &v : m_map)
	{
		for (Material x : v)
			std::cout << x.getName() << ' ';
		std::cout << std::endl;
	}
}

int returnProbability(int randNum) {
	return randNum <= 70 ? 0 :
		randNum <= 75 ? 1 :
		randNum <= 80 ? 2 :
		randNum <= 85 ? 3 :
		randNum <= 89 ? 4 :
		randNum <= 93 ? 5 :
		randNum <= 97 ? 6 :
		randNum <= 99 ? 7 :
		8;
}

std::string determineMineral(__int64 index) {
	std::string getMinerals = "SELECT mineralName, mineralFrequency FROM minerals";
	/*
	while (sqlite3_column_text(getMinerals, 0))
	{
		for (int i = 0; i < 2; i++)
			result[i].push_back(std::string((char *)sqlite3_column_text(getMinerals, i)));
		sqlite3_step(getMinerals);
	}
	*/
	std::array<std::string, 9> minerals = { "dirt", "stone","bronze","silver", "iron", "gold","ruby","emerald","diamond" }; //stone to be added
	std::array<int, 9> probabilities = { 70, 75, 80, 85, 89, 93, 97, 99, 100 };
	auto mineralsSize = minerals.size();
	int randNum;
	//Preset blocks
	if (index < WorldInfo::b_sky_height) { return "sky"; }
	else if (index == WorldInfo::b_sky_height) { return "grass"; }

	//Randomly assign minerals
	if (index > 0.9 * WorldInfo::b_world_height) {			
		randNum = rand() % 100 + 1;
	}
	else if (index > 0.6 * WorldInfo::b_world_height) {
		randNum = rand() % 99 + 1;
	}
	else if (index > 0.3 * WorldInfo::b_world_height) {
		randNum = rand() % 93 + 1;
	}
	else {
		randNum = rand() % 80 + 1;
	}
	return minerals[returnProbability(randNum)];
}


std::vector<std::vector<Material>> Map::GenerateMap() {
	srand((unsigned int)time(NULL));		//Sets a random seed everytime solution is built

	//Create a 2d Vector
	std::vector<std::vector<Material>> matrix(WorldInfo::b_world_height, std::vector<Material>(WorldInfo::b_world_width));

	//Declare iterators to go through 2d vector
	std::vector<std::vector<Material>>::iterator row;
	std::vector<Material>::iterator col;

	//Traverse vector and set up initial values
	for (int y = 0; y < WorldInfo::b_world_height; ++y) {
		for (int x = 0; x < WorldInfo::b_world_width; ++x) {
			std::string mineral = determineMineral(y);
			Material *newMin = new Material(mineral);					//Create new material object from the randomly chosen

			newMin->setX(x);
			newMin->setY(y);
			matrix[y][x] = *newMin;	//Add object to matrix
		}
	}
	return matrix;
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

void Map::render(int camXCoords, int camYCoords, int camX, int camY, int xEdge, int yEdge)
{
	for (int y = camYCoords; y < yEdge; y++) {
		for (int x = camXCoords; x < xEdge; x++) {
			std::string type; // block id
			type = matrix[y][x].getName();
			dest.x = (x * Winfo::block_size) - camX;
			dest.y = (y * Winfo::block_size) - camY;

			if (type == "grass") {
				TextureManager::Draw(grass, src, dest);
			}
			else if (type == "dirt") {
				TextureManager::Draw(dirt, src, dest);
			}
			else if (type == "stone") {
				TextureManager::Draw(stone, src, dest);
			}
			else if (type == "bronze") {
				TextureManager::Draw(bronze, src, dest);
			}
			else if (type == "silver") {
				TextureManager::Draw(silver, src, dest);
			}
			else if (type == "iron") {
				TextureManager::Draw(iron, src, dest);
			}
			else if (type == "gold") {
				TextureManager::Draw(gold, src, dest);
			}
			else if (type == "ruby") {
				TextureManager::Draw(ruby, src, dest);
			}
			else if (type == "emerald") {
				TextureManager::Draw(emerald, src, dest);
			}
			else if (type == "diamond") {
				TextureManager::Draw(diamond, src, dest);
			}
		}
	}
}
