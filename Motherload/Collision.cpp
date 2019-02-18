#include "Collision.h"

void Collision::MovePlayer(Map *m, Player *p, int dx, int dy) {
	
	// if the following block is air, let player move, else stop him and move him to block touching point
	// you have to axis for that
	// Ending grid coordinate must be air!!!!
	bool vertEnabled = true,
		horEnabled = true;

	if (vertEnabled) Collision::MoveVertically(m, p, dx, dy);
	else p->DeltaCoords(0, dy);

	if (horEnabled) Collision::MoveHorizontally(m, p, dx, dy);
	else p->DeltaCoords(dx, 0);	
}

void Collision::MoveVertically(Map *m, Player *p, int dx, int dy) {
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
		p->DeltaCoords(dx, 0);
		std::cout << (p->PosX() + 32) % 64 << std::endl;
	}
}

void Collision::MoveHorizontally(Map *m, Player *p, int dx, int dy) {
	int pretendedX = p->PosX() + dx + Winfo::block_size / 2,
		pretendedY = p->PosY() + dy + Winfo::block_size;
}
