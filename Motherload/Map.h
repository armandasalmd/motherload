#ifndef Map_h

#define Map_h
#include "Game.h"
#include <vector>
#include <iostream>
#include "StaticVars.h"

class Map {
public:
	Map();
	~Map();

	void LoadMap(std::vector<std::vector<int>> m_map); // loads given map
	void LoadMap(); // loads map creating new one
	void DrawMap(); // shows MAP on the screen
	static int *GetGridCordinates(int x, int y);

	void PrintMap(std::vector<std::vector<int>> m_map);

private:
	SDL_Rect src, dest;
	SDL_Texture *dirt;
	SDL_Texture *grass;
	SDL_Texture *water;
	
	std::vector<std::vector<int>> map; // [row][column]

	std::vector<std::vector<int>> GenerateMap(); // creates new map
};
#endif /* Game_hpp */