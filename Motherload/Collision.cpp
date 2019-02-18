#include "Collision.h"

void Collision::MovePlayer(Map *m, Player *p, int dx, int dy) {
	// if the following block is air, let player move, else stop him and move him to block touching point
	// you have to axis for that
	// Ending grid coordinate must be air!!!!
	bool vertEnabled = true, // enable vertical collision
		horEnabled = true; // enable horizontal collision

	Coord cDelta; // delta coordinates
	cDelta.x = dx;
	cDelta.y = dy;

	if (vertEnabled) Collision::MoveVertically(m, p, cDelta);
	else p->DeltaY(dy);

	if (horEnabled) Collision::MoveHorizontally(m, p, cDelta);
	else p->DeltaX(dx);
}

void Collision::MoveVertically(Map *m, Player *p, Coord cDelta) {
	int pretendedX = p->PosX() + cDelta.x + Winfo::block_size / 2,
		pretendedY = p->PosY() + cDelta.y + Winfo::block_size;

	int *pretGridCoords = m->GetGridCordinates(pretendedX, pretendedY);

	Mineral pretendedMineral = m->GetMap()[pretGridCoords[1]][pretGridCoords[0]];
	Map::TexturePath pretendedPath = m->GetTexturePath(pretendedMineral.getName());
	if (BlockList::SKY == pretendedPath.blockId)
		p->DeltaCoords(cDelta.x, cDelta.y);
	else {

		//std::cout << pretendedMineral.getY() << std::endl;
		if (p->PosY() % Winfo::block_size != 0) {
			p->SetCoords(p->PosX(), (pretendedMineral.getY() - 1) * Winfo::block_size);
		}
		p->DeltaCoords(cDelta.x, 0);
		//std::cout << (p->PosX() + 32) % 64 << std::endl;
	}
}

void Collision::MoveHorizontally(Map *m, Player *p, Coord cDelta) {
	Coord cStepped;
	cStepped.x = p->PosX() + cDelta.x + Winfo::block_size / 2;
	cStepped.y = p->PosY() + cDelta.y + Winfo::block_size;
	int player_x_pos_on_block = (p->PosX() + Winfo::block_size / 2) % Winfo::block_size - Winfo::block_size / 2; // values: [-32; 32], 0 is middle

	if (player_x_pos_on_block > 20) { // you hit right wall
		std::cout << "I hit right wall" << player_x_pos_on_block << std::endl;
	}
	else if (player_x_pos_on_block < -20) { // you hit left wall
		std::cout << "I hit left wall" << player_x_pos_on_block << std::endl;
	}
	else { // all fine, you hit air
		p->DeltaX(cDelta.x);
	}
	

	//if ()
	



}


