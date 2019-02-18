#include "Collision.h"

Collision::Collision() {
	std::cout << "Collision class initialized!" << std::endl;
}


void Collision::MovePlayer(Map *m, Player *p, int dx, int dy) {
	
	// if the following block is air, let player move, else stop him and move him to block touching point
	// you have to axis for that
	// Ending grid coordinate must be air!!!!

	int pretendedX = p->PosX() + dx + Winfo::block_size / 2, 
		pretendedY = p->PosY() + dy + Winfo::block_size;

	int *pretGridCoords = m->GetGridCordinates(pretendedX, pretendedY);

	Mineral pretendedMineral = m->GetMap()[pretGridCoords[1]][pretGridCoords[0]];
	Map::TexturePath pretendedPath = m->GetTexturePath(pretendedMineral.getName());
	if (BlockList::SKY == pretendedPath.blockId)
		p->DeltaCoords(dx, dy);
	else {

		//std::cout << pretendedMineral.getY() << std::endl;
		if (p->PosY() % Winfo::block_size != 0) {
			p->SetCoords(p->PosX(), (pretendedMineral.getY() - 1) * Winfo::block_size);
		}
		p->SetCoords(pretendedX - 32, p->PosY());
		std::cout << (p->PosX() + 32) % 64 << std::endl;
	}
		


		//std::cout << "We have a collition detected " << pretendedPath.name << std::endl;

	//int newx = 0, newy = 0;
	
}