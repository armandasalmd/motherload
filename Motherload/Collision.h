#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Mining.h"
#include "Game.h"
// Used in buildings detection:
#include "Models.h"
#include "ModelObjects.h"
#include "StaticVars.h"

class Collision {

public:
	static void MovePlayer(Game *game, Map *m, Player *p, int dx, int dy);
private:
	static void MoveHorizontally(Game *game, Map *m, Player *p, Coord cDelta);
	static void MoveVertically(Game *game, Map *m, Player *p, Coord cDelta);
	static void DetectBuildingCollision(Game *game, Player *p);
};