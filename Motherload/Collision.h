#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"

class Collision {

public:
	static void MovePlayer(Map *m, Player *p, int dx, int dy);

private:
	static void MoveHorizontally(Map *m, Player *p, Coord cDelta);
	static void MoveVertically(Map *m, Player *p, Coord cDelta);

};