#ifndef Map_h

#define Map_h
#include "Game.h"
#include <vector>
#include <iostream>
#include "StaticVars.h"
#include <string>
#include <fstream>
#include <sstream>

class Map {
public:
	Map();
	~Map();

	void LoadMap(char *path); // loads given map
	void LoadMap(); // loads map creating new one
	void SaveMap(char *path); // saves map into given file

	void DrawMap(); // shows MAP on the screen
	static int *GetGridCordinates(int x, int y);

	void PrintMap(std::vector<std::vector<int>> m_map);

private:
	SDL_Rect src, dest;

	const char *paths_file = "assets/block_paths.txt";
	std::vector<std::string> block_paths;
	
	std::vector<std::vector<int>> map; // [row][column]
	std::vector<std::vector<int>> GenerateMap(); // creates new map

	void LoadBlockPaths();
};
#endif /* Game_hpp */