// <summary>General player class responsible for its drawing on the map,
//     coordnates manipulation and control of player model</summary>
// <author>barkausa</author>
// <collab>living11</collab>

#pragma once
#include "TextureObject.h"
#include "ModelObjects.h"
#include "Models.h"
#include "Mineral.h"

class Player: public TextureObject {
public:
	// Constructors
	Player(const char *path) : TextureObject(path) {}
	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {}

	// Camera position movement on the screen function
	void Step(const int dx, const int dy);

	// __________ Getters ___________
	// Player pixel coordinates
	int PosX() { return positionX; }
	int PosY() { return positionY; }
	bool IsInAir() { return in_air; }
	
	// __________ Setters ___________
	// Player map coordinates
	void SetCoords(int x, int y);
	void SetX(int x) { positionX = x; };
	void SetY(int y) { positionY = y; };
	void SetInAir(bool value) { in_air = value; }

	// __________ Player Movement __________
	// Move player pixel coordinates around the map
	void DeltaCoords(int dx, int dy) { SetCoords(positionX + dx, positionY + dy); }
	void DeltaX(int dx) { SetCoords(positionX + dx, positionY); }
	void DeltaY(int dy) { SetCoords(positionX, positionY + dy); }

	// ========== START collaborator: living11 ==========
	// player balance functions
	int getPlayerBalance() { return cashBalance; }
	void setPlayerBalance(int newBalance) { cashBalance = newBalance; }
	void increasePlayerBalance(int balanceIncrease) { cashBalance = cashBalance + balanceIncrease; }
	void decreasePlayerBalance(int balanceDecrease) { 
		if (cashBalance - balanceDecrease < 0) { 
			throw "Not enough cash"; 
		} else 
			cashBalance = cashBalance - balanceDecrease; 
	}

	// Player fuel functions
	int getPlayerFuel() { return fuelAmount; }
	void setPlayerFuel(int newFuelLevel) { fuelAmount = newFuelLevel; }
	void increaseFuel(int fuelIncrease) {fuelAmount = fuelAmount + fuelIncrease ; }
	void decreaseFuel(int fuelDecrease) { if (fuelAmount - fuelDecrease <= 0) { throw "Tank empty"; } else  fuelAmount = fuelAmount - fuelDecrease;  }
	// ========== END collaborator: living11 ==========

	// __________ Interaction with database __________
	void loadPlayerModel(int player_id);
	void savePlayerModel();
	PlayerModel getPlayerModel();
	void addMineralToInv(Mineral item);
private:
	int positionX = 0;	// player x position in pixels on the map
	int positionY = 0;	// player y position in pixels on the map

	bool in_air;
	PlayerModel pModel; // model encapsulation
	
	int cashBalance = 500;
	int fuelAmount = 100;
};