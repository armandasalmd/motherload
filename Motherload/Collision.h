// <summary>handles player collision with a block. 
//     Also detects touched building on surface</summary>
// <author>barkausa</author>

#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Mining.h"
#include "Game.h"
// <remarks>Used for buildings detection:
#include "Models.h"
#include "ModelObjects.h"
#include "StaticVars.h"
// </remarks>

class Collision {
public:
	/*
	<summary>general func that triggers horizontal and vertical 
		collision funcs, change game state if building touched
	</summary>
	<param name="game">current game instance</param>
	<param name="map">current map instance</param>
	<param name="p">current player instance</param>
	<param name="dx">delta x - request to move vertically</param>
	<param name="dy">delta y - request to move horizontally</param>
	*/
	static void MovePlayer(Game *game, Map *m, Player *p, int dx, int dy);
	/*
	<summary>changes game state if building was touched</summary>
	<param name="map">current map instance</param>
	<param name="p">current player instance</param>
	*/
	static void DetectBuildingCollision(Game *game, Player *p);
private:
	// __________ Collision detection __________
	/*
	<summary>Detects collision, if so moves player close to the block</summary>
	<param name="cDelta">requested coords to move</param>
	*/
	static void MoveHorizontally(Game *game, Map *m, Player *p, Coord cDelta);
	/*
	<summary>Detects collision, if so moves player close to the block</summary>
	<param name="cDelta">requested coords to move</param>
	*/
	static void MoveVertically(Game *game, Map *m, Player *p, Coord cDelta);
};