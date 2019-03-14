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
	// __________ Constructors __________
	Player(const char *path) : TextureObject(path) {}
	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {}

	// __________ Getters ___________
	// Player absolute pixel coordinates
	int PosX() { return positionX; }
	int PosY() { return positionY; }
	// Returns True if player is flying
	bool IsInAir() { return in_air; }
	PlayerModel getPlayerModel();
	
	// __________ Setters ___________
	// Sets Player absolute map coordinates
	void SetCoords(int x, int y);
	void SetX(int x) { positionX = x; };
	void SetY(int y) { positionY = y; };
	// Set True if player is flying
	void SetInAir(bool value) { in_air = value; }

	// __________ Player Movement __________
	// Change/Move player absolute(px) coordinates
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
	/* <summary>Loads player model into private var: pModel</summary> */
	void loadPlayerModel(int player_id);
	/* <summary>Saves player status and Inventory</summary> */
	void savePlayerModel();
	/* 
	<summary>Adds item to game inventory</summary>
	<remarks>It do not update DB</remarks>
	<params name="item">mined mineral info</params>
	*/
	void addMineralToInv(Mineral item);
private:
	int positionX = 0;	// player x absolute position(px) on the map
	int positionY = 0;	// player y absolute position(px) on the map

	bool in_air;		// true: player is flying
	PlayerModel pModel; // model encapsulation
	
	// ========== START collaborator: living11 ==========
	int cashBalance = 500;
	int fuelAmount = 100;
	// ========== END collaborator: living11 ==========
};