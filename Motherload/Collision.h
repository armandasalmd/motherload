#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Mining.h"
#include "Game.h"
#include "Models.h"
#include "ModelObjects.h"
#include "StaticVars.h"

// summary:
//		handles player collision with a block. 
//      Also detects touched building on surface
// author:
//		barkausa
class Collision {
public:
	// summary:
	//		general func that triggers horizontal and vertical 
	//		collision funcs, change game state if building touched
	// param:
	//		game: current game instance
	//		map:  current map instance
	//		p:	  current player instance
	//		dx:	  delta x - request to move vertically
	//		dy:	  delta y - request to move vertically
	static void MovePlayer(Game *game, Map *m, Player *p, int dx, int dy);

	// summary:
	//		changes game state if building was touched
	// param:
	//		map:  current map instance
	//		p:	  current player instance
	static void DetectBuildingCollision(Game *game, Player *p);
private:
	// ------------ Collision detection -------------

	// summary:
	//		Detects collision, if so moves player close to the block
	// param:
	//		cDelta: requested coords to move
	static void MoveHorizontally(Game *game, Map *m, Player *p, Coord cDelta);
	
	// summray:
	//		Detects collision, if so moves player close to the block
	// param:
	//		cDelta: requested coords to move
	static void MoveVertically(Game *game, Map *m, Player *p, Coord cDelta);
};