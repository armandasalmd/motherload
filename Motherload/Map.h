#pragma once
#ifndef Map_h
#define Map_h

#include "Game.h"
#include "minerals.h"
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
	enum BlockList {
		SKY= 0, GRASS, DIRT, STONE, BRONZE, SILVER, IRON, GOLD, RUBY, EMERALD, DIAMOND
	}; //Maps each mineral (block) to a integer value.

	struct TexturePath {
		BlockList blockId;
		std::string name;
		std::string path;
		SDL_Texture* tex;
	};

	Map(Player *player);
	~Map();

	//void LoadMap(char *path); // loads given map
	void LoadMap(); // loads map creating new one
	void SaveMap(char *path); // saves map into given file
	void render(int camXCoords, int camYCoords, int camX, int camY, int xEdge, int yEdge);
	void PrintMap(std::vector<std::vector<Material>> m_map);
	void setMap(std::vector<std::vector<Material>> newMap) { this->matrix = newMap; }
	void LoadBlockPaths();
	void DrawMap(Camera cam); // shows MAP on the screen

	//std::vector<Material> getMap();
	static int *GetGridCordinates(int x, int y);
	
	std::vector<std::vector<Material>> getMap() { return this->matrix; }

private:
	SDL_Rect src, dest;

	/*SDL_Texture *dirt;
	SDL_Texture *grass;
	SDL_Texture *water;
	SDL_Texture *stone;
	SDL_Texture *bronze;
	SDL_Texture *silver;
	SDL_Texture *iron;
	SDL_Texture *gold;
	SDL_Texture *ruby;
	SDL_Texture *emerald;
	SDL_Texture *diamond;
*/
	Player *player;

	const char *paths_file = "assets/block_paths.txt";

	std::vector<TexturePath> block_paths;
	std::vector<std::vector<Material>> matrix; // [row][column]
	std::vector<std::vector<Material>> GenerateMap(); // creates new map
};
#endif // Game_hpp 