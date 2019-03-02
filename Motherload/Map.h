#pragma once
#ifndef Map_h
#define Map_h

#include "Game.h"
#include "Mineral.h"
#include "StaticVars.h"
#include "player.h"
#include "TextureManager.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <array>
#include <ctime>

#include "Camera.h"

class Map {
public:
	//Maps each mineral (block) to a integer value.
	
	struct TexturePath {
		BlockList blockId;
		std::string name;
		std::string path;
		SDL_Texture* tex;
	};
	
	Map(Player *player);
	~Map();

	void LoadMap(); // loads map creating new one
	void SaveMap(char *path); // saves map into given file
	static int *GetGridCordinates(int x, int y); // Armandas function
	TexturePath GetTexturePath(std::string blockName);

	/* _____________________ Brad's functions _____________________ */
	void Render(int camXCoords, int camYCoords, int camX, int camY, int xEdge, int yEdge);
	void PrintMap(std::vector<std::vector<Mineral>> m_map);
	std::vector<std::vector<Mineral>> &GetMap() { return matrix; }
	void SetMap(std::vector<std::vector<Mineral>> newMap) { this->matrix = newMap; }
	void DrawMap(Camera cam); // shows MAP on the screen
	/* ____________________________________________________________ */

	

private:
	SDL_Rect src, dest;
	Player *player;

	const char *paths_file = "assets/block_paths.txt";
	std::vector<TexturePath> block_paths;
	std::vector<std::vector<Mineral>> matrix; // [row][column]
	std::vector<std::vector<Mineral>> GenerateMap(); // creates new map

	void LoadBlockPaths(); // Armandas function
	int ReturnProbability(std::array<int, 9> probabilities, int randNum);
	std::string determineMineral(__int64 index);
};
#endif // Game_hpp 