#pragma once
#include "Map.h"
#include "Camera.h"

//#include <fstream>
//#include <sstream>

Map::Map(Player *player) {
	// map initialization
	LoadBlockPaths();
	LoadMap();
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
	std::string extension = "";
	std::string temp;
	TexturePath mineralPath;

	if (fd.is_open()) {
		fd >> folder >> folder;
		fd >> extension >> extension;
		int i = 0;
		while (!fd.eof()) {
			fd >> temp;
			mineralPath.blockId = (BlockList)i;
			mineralPath.path = folder + temp + extension;
			mineralPath.name = temp;
			mineralPath.tex = TextureManager::LoadTexture(mineralPath.path);

			block_paths.push_back(mineralPath);
			mineralPath = TexturePath();
			//std::cout << "blockID:" << mineralPath.blockId << " path:" << mineralPath.path << std::endl;
			i++;
		}
	}
	fd.close();

	/*for (std::vector<std::string>::iterator it = begin(block_paths); it != end(block_paths); it = next(it))
		std::cout << *it << std::endl;*/
}

/*void Map::LoadMap(char *path) {
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
}*/

void Map::LoadMap() { // generates new world
	this->matrix = GenerateMap();
	//PrintMap(matrix);
}

/*void Map::SaveMap(char *path) {
	std::ofstream fr;
	fr.open(path);
	if (fr.is_open())
		for (const std::vector<int> &v : map) {
			for (int x : v)
				fr << x << ' ';
			fr << '\n';
		}
	fr.close();
}*/

void Map::DrawMap(Camera cam)
{
	int *camCoords = cam.calcCameraCoordinates();
	int camXCoords = camCoords[0] / 64;
	int camYCoords = camCoords[1] / 64;
	int xEdge;
	int yEdge;
	bool xLimit = WorldInfo::b_world_width - (camXCoords + Winfo::blocks_x + 1) >= 0;
	bool yLimit = WorldInfo::b_world_height - (camYCoords + Winfo::blocks_y + 1) >= 0;

	if (xLimit && yLimit) {
		yEdge = camYCoords + Winfo::blocks_y + 1;
		xEdge = camXCoords + Winfo::blocks_x + 1;
	}
	else if (xLimit && !yLimit) {
		yEdge = WorldInfo::b_world_height;
		xEdge = camXCoords + Winfo::blocks_x + 1;
	}
	else if (!xLimit && yLimit) {
		xEdge = WorldInfo::b_world_width;
		yEdge = camYCoords + Winfo::blocks_y + 1;
	}
	else {
		xEdge = WorldInfo::b_world_width;
		yEdge = WorldInfo::b_world_height;
	}
	this->Render(camXCoords, camYCoords, camCoords[0], camCoords[1], xEdge, yEdge);
}

void Map::PrintMap(std::vector<std::vector<Mineral>> m_map) {
	for (const std::vector<Mineral> &v : m_map)
	{
		for (Mineral x : v)
			std::cout << x.getName() << ' ';
		std::cout << std::endl;
	}
}

int Map::ReturnProbability(std::array<int, 9> probabilities, int randNum) {
	return randNum <= 84 ? 0 :
		randNum <= 86 ? 1 :
		randNum <= 88 ? 2 :
		randNum <= 90 ? 3 :
		randNum <= 92 ? 4 :
		randNum <= 94 ? 5 :
		randNum <= 96 ? 6 :
		randNum <= 98 ? 7 :
		8;
}

std::string Map::determineMineral(__int64 index) {
	std::string getMinerals = "SELECT mineralName, mineralFrequency FROM minerals";
	/*
	while (sqlite3_column_text(getMinerals, 0))
	{
		for (int i = 0; i < 2; i++)
			result[i].push_back(std::string((char *)sqlite3_column_text(getMinerals, i)));
		sqlite3_step(getMinerals);
	}
	*/
	std::array<std::string, 9> minerals = { "dirt", "stone","bronze","silver", "iron", "gold","ruby","emerald","diamond" };
	std::array<int, 9> probabilities = { 84, 86, 88, 90, 92, 94, 96, 98, 100 };
	//70, 75, 80, 85, 89, 93, 97, 99, 100
	auto mineralsSize = minerals.size();
	int randNum;
	//Preset blocks
	if (index < WorldInfo::b_sky_height) { return "sky"; }
	else if (index == WorldInfo::b_sky_height) { return "grass"; }

	//Randomly assign minerals
	if (index > 0.9 * WorldInfo::b_world_height) {
		randNum = rand() % probabilities[8] + 1;
	}
	else if (index > 0.6 * WorldInfo::b_world_height) {
		randNum = rand() % probabilities[7] + 1;
	}
	else if (index > 0.3 * WorldInfo::b_world_height) {
		randNum = rand() % probabilities[5] + 1;
	}
	else {
		randNum = rand() % probabilities[2] + 1;
	}
	return minerals[ReturnProbability(probabilities, randNum)];
}

std::vector<std::vector<Mineral>> Map::GenerateMap() {
	//Sets a random seed everytime solution is built
	srand((unsigned int)time(NULL));

	//Create a 2d Vector
	std::vector<std::vector<Mineral>> matrix(WorldInfo::b_world_height, std::vector<Mineral>(WorldInfo::b_world_width));

	//Declare iterators to go through 2d vector
	std::vector<std::vector<Mineral>>::iterator row;
	std::vector<Mineral>::iterator col;

	//Traverse vector and set up initial values
	for (int y = 0; y < WorldInfo::b_world_height; ++y) {
		for (int x = 0; x < WorldInfo::b_world_width; ++x) {
			//Create new material object from the randomly chosen
			std::string mineral = determineMineral(y);
			Mineral *newMin = new Mineral(mineral);
			newMin->setX(x);
			newMin->setY(y);
			matrix[y][x] = *newMin;	//Add object to matrix
		}
	}

	Mineral *newMin = new Mineral("sky");
	
	// temp map manipulator
	matrix[5][5] = *newMin;
	matrix[6][5] = *newMin;
	matrix[6][6] = *newMin;
	matrix[7][5] = *newMin;
	matrix[7][4] = *newMin;
	// end

	return matrix;
}


void Map::Render(int camXCoords, int camYCoords, int camX, int camY, int xEdge, int yEdge)
{
	for (int y = camYCoords; y < yEdge; y++) {
		for (int x = camXCoords; x < xEdge; x++) {
			std::string type; // block id
			type = matrix[y][x].getName();
			dest.x = (x * Winfo::block_size) - camX;
			dest.y = (y * Winfo::block_size) - camY;
			TexturePath selectedPath;
			for (TexturePath value : block_paths) {
				if (value.name == type) {
					selectedPath = value;
					break;
				}
			}

			if (selectedPath.name != "sky") {
				TextureManager::Draw(selectedPath.tex, src, dest);
			}
		}
	}
}

int *Map::GetGridCordinates(int x, int y) { // Armandas function
	int *mArr = new int[2]{ -1, -1 };
	if (Winfo::block_size != 0) {
		mArr[0] = x / Winfo::block_size;
		mArr[1] = y / Winfo::block_size;
	}
	return mArr;
}

// Armandas function
Map::TexturePath Map::GetTexturePath(std::string blockName) {
	for (TexturePath t: block_paths)
		if (t.name == blockName)
			return t;
	return Map::TexturePath();
}