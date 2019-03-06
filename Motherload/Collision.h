#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Mining.h"
#include "Game.h"

class Collision {

public:
	static void MovePlayer(Game *game, Map *m, Player *p, int dx, int dy);
private:
	static void MoveHorizontally(Game *game, Map *m, Player *p, Coord cDelta);
	static void MoveVertically(Game *game, Map *m, Player *p, Coord cDelta);
};