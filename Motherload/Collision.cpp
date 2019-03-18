#include "Collision.h"

/*
	Horizontal movement collision logic:
	+ determine if player is more left/right
	+ if right calculate right sprite points, if left calculate left sprite points (40x48)
	+ convert it to grid coordinates
	+ if points are the same coordinate, then check one of them
	+ else point 1 has to pass the test and point 2 has to pass it to move that direction
	+ if the test is passed (blocks are air), then default move
	+ else (if failed the test) take that grid coordinate 
	  wall and pull player to its left/right x coord as close as possib.
	+ new player coord = wall left or right coord px on map ------ 
	  player x(+40 if right wall) coord
*/

void Collision::MovePlayer(Game *game, Map *m, Player *p, int dx, int dy) {
	// Collision logic:
	//		if the following block is air, let player move, 
	//		else stop him and move closiest to the block
	bool vertEnabled = true, // enable vertical collision
		 horEnabled	 = true; // enable horizontal collision

	Coord cDelta; // delta(move amount) coordinates
	cDelta.x = dx;
	cDelta.y = dy;

	if (vertEnabled) Collision::MoveVertically(game, m, p, cDelta);
	else p->DeltaY(dy); // default move

	if (horEnabled) Collision::MoveHorizontally(game, m, p, cDelta);
	else p->DeltaX(dx); // default move
	DetectBuildingCollision(game, p); // changes game state if player hovers on building
}

void Collision::DetectBuildingCollision(Game *game, Player *p) {
	BuildingModel building;
	int fromX, toX; // building detection limits for X
	int player_pos_x = p->PosX() + Winfo::block_size / 2; // player x coord(texture middle)

	// activates buildings detection when player y=4 (on the surface)
	if (p->PosY() / Winfo::block_size == 4) {
		// iterating 4 buildings:
		// FUEL STATION, MARKET, UPGRADES SHOP, SAVE FLAG
		int xDetectionOffset[] = {Winfo::block_size / 2, Winfo::block_size, Winfo::block_size / 2, 0};
		/*for (int i = 0; i < 4; i++) {
			// Getting building model from database
			if (i == 3) {
				// save flag has discrepancy with: 
				// enum State number and building_id in database,
				// thus special case!
				building = building = Models::getInstance()->getBuildingById(0);
			}
			else
				building = building = Models::getInstance()->getBuildingById(i + 1);
			
			fromX = building.getBuildingX() * Winfo::block_size + xDetectionOffset[i];
			toX = fromX + Winfo::block_size;
			if (player_pos_x >= fromX && player_pos_x <= toX) {
				game->setState((State)(i + 3));
				return;
			}
		}*/
		/* ============== Repetitive/Old version ================= */

		// FUEL STATION detection
		building = building = Models::getInstance()->getBuildingById(1); // Fuel station
		fromX = building.getBuildingX() * Winfo::block_size + Winfo::block_size / 2;
		toX = fromX + Winfo::block_size;
		if (player_pos_x >= fromX && player_pos_x <= toX) {
			game->setState(State::GasStation);
			return;
		}
		// MARKET detection
		building = building = Models::getInstance()->getBuildingById(2); // Market station
		fromX = building.getBuildingX() * Winfo::block_size + Winfo::block_size;
		toX = fromX + Winfo::block_size;
		if (player_pos_x >= fromX && player_pos_x <= toX) {
			game->setState(State::Market);
			return;
		}
		// UPGRADES SHOP detection
		building = building = Models::getInstance()->getBuildingById(3); // Upgrades shop
		fromX = building.getBuildingX() * Winfo::block_size + Winfo::block_size;
		toX = fromX + Winfo::block_size;
		if (player_pos_x >= fromX && player_pos_x <= toX) {
			game->setState(State::UpgradesShop);
			return;
		}
		// SAVE FLAG detection
		building = building = Models::getInstance()->getBuildingById(0); // Save flag
		fromX = building.getBuildingX() * Winfo::block_size;
		toX = fromX + Winfo::block_size;
		if (player_pos_x >= fromX && player_pos_x <= toX) {
			game->setState(State::Save);
			return;
		}
	}
	game->setState(State::InGame); // default state
}

void Collision::MoveVertically(Game *game, Map *m, Player *p, Coord cDelta) { // controls up/down
	int saved_y_pos = p->PosY(); // used for in_air calculation
	if (cDelta.y == 0) // Case: NO movement
		return;
	// Stepped player boundaries
	int x1 = p->PosX() + 12 ,			// xLeft
		x2 = p->PosX() + 52 - 1 ;		// xRight
	int y1 = p->PosY() + 16 + cDelta.y, // yTop
		y2 = p->PosY() + 64 + cDelta.y; // yBottom

	// storing player box coordinates
	int* points[4]; // multidimentional array
	points[0] = Map::GetGridCordinates(x1, y1); // top left
	points[1] = Map::GetGridCordinates(x2, y1); // top right
	points[2] = Map::GetGridCordinates(x2, y2); // bottom right
	points[3] = Map::GetGridCordinates(x1, y2); // bottom left

	// player position on the block in range: [-32;32]
	int block_pos = (y1 + y2) / 2 % 64 - 32;
	// minerals that player is moving towards
	Mineral m1, m2;
	// false if player is colliding with 2 blocks
	bool sameBlock = false;

	if (block_pos < -8) { // player touch top wall
		m1 = m->GetMap()[points[0][1]][points[0][0]]; // getting mineral object
		if (!(points[0][0] == points[1][0] && points[0][1] == points[1][1])) //touches two blocks
			m2 = m->GetMap()[points[1][1]][points[1][0]];
		else //touches one block
			sameBlock = true;
		if (m1.getName() == "sky" && (sameBlock || m2.getName() == "sky"))
			p->DeltaY(cDelta.y);
		else 
			p->SetY((points[0][1] + 1) * 64 - 16);
	}
	else if (block_pos > 8) { // player touch bottom
		if (game->getYpress() == 'd') { Mining::mineBlock(m, p, (p->PosX() + 32) / 64, p->PosY() / 64 + 1); }
		m1 = m->GetMap()[points[2][1]][points[2][0]];
		
		if (!(points[2][0] == points[3][0] && points[2][1] == points[3][1])) {
			// player touches two blocks (collision blocks has same coordinates)
			m2 = m->GetMap()[points[3][1]][points[3][0]];
		}
		else //touches one block
			sameBlock = true;
		if (m1.getName() == "sky" && (sameBlock || m2.getName() == "sky")) {
			// if collision block(s) is sky - let to move
			p->DeltaY(cDelta.y);
		}
		else {
			// collision block(s) is not sky - move to closiest point
			p->SetY((points[2][1] - 1) * 64);
		}
	}
	else // if no collision found, move like default
		p->DeltaY(cDelta.y);
	p->SetInAir(saved_y_pos != p->PosY()); // true if y coord changed
}

void Collision::MoveHorizontally(Game *game, Map *m, Player *p, Coord cDelta) { // controls left/right
	// Stepped player boundaries
	if (cDelta.x == 0)
		return;
	int x1 = p->PosX() + 12 + cDelta.x,		// xLeft
		x2 = p->PosX() + 52 - 1 + cDelta.x; // xRight
	int y1 = p->PosY() + 16,				// yTop
		y2 = p->PosY() + 64 - 1;			// yBottom

	// storing player box coordinates
	int* points[4]; // multidimentional array
	points[0] = Map::GetGridCordinates(x1, y1); // top left
	points[1] = Map::GetGridCordinates(x2, y1); // top right
	points[2] = Map::GetGridCordinates(x2, y2); // bottom right
	points[3] = Map::GetGridCordinates(x1, y2); // bottom left

	// player position on the block in range: [-32;32]
	int block_pos = (x1 + x2) / 2 % 64 - 32 + 1;
	// minerals that player is moving towards
	Mineral m1, m2;
	// false if player is colliding with 2 blocks
	bool sameBlock = false;

	if (block_pos > 12) { // player touch right wall
		if (game->getXpress() == 'r') { Mining::mineBlock(m, p, p->PosX() / 64 + 1, (p->PosY() + 32) / 64); }
		m1 = m->GetMap()[points[1][1]][points[1][0]]; // getting mineral object
		if (!(points[1][0] == points[2][0] && points[1][1] == points[2][1])) {
			// player touches two blocks (collision blocks has same coordinates)
			m2 = m->GetMap()[points[2][1]][points[2][0]];
		}
		else // player touches one block
			sameBlock = true;
		if (m1.getName() == "sky" && (sameBlock || m2.getName() == "sky"))
			p->DeltaX(cDelta.x);
		else {
			//int xBlockCoord = points[1][0] * Winfo::block_size;
			//p->SetX(xBlockCoord - 53);
			p->SetX(points[0][0] * 64 + 12);
		}
	}
	else if (block_pos < -12) { // player touch left wall
		if (game->getXpress() == 'l') { Mining::mineBlock(m, p, p->PosX() / 64, (p->PosY() + 32) / 64); }
		m1 = m->GetMap()[points[0][1]][points[0][0]];
		if (!(points[0][0] == points[3][0] && points[0][1] == points[3][1])) // two blocks touched left
			m2 = m->GetMap()[points[3][1]][points[3][0]];
		else
			sameBlock = true;
		if (m1.getName() == "sky" && (sameBlock || m2.getName() == "sky")) {
			// if collision block(s) is sky - let to move
			p->DeltaX(cDelta.x);
		}
		else {
			// collision block(s) is not sky - move to closiest point
			p->SetX((points[0][0] + 1) * 64 - 12);
		}
	}
	else // if no collision found, move like default 
		p->DeltaX(cDelta.x);
}