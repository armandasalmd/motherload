#pragma once
#include "TextureObject.h"

class Player: public TextureObject {
public:
	Player(const char *path) : TextureObject(path) {}

	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {}

	// camera position regulation on the screen function
	void Step(const int dx, const int dy);

	// player map coordinates
	int PosX() { return positionX; }
	int PosY() { return positionY; }
	
	// player map coordinates function
	void SetCoords(int x, int y);
	void SetX(int x) { positionX = x; };
	void SetY(int y) { positionY = y; };
	
	// set in air
	bool IsInAir() { return in_air; }
	void SetInAir(bool value) { in_air = value; }

	// player map coordinates function
	void DeltaCoords(int dx, int dy) { SetCoords(positionX + dx, positionY + dy); }
	void DeltaX(int dx) { SetCoords(positionX + dx, positionY); }
	void DeltaY(int dy) { SetCoords(positionX, positionY + dy); }

	// player balance functions
	int getPlayerBalance() { return cashBalance; }
	void setPlayerBalance(int newBalance) { cashBalance = newBalance; }
	void increasePlayerBalance(int balanceIncrease) { cashBalance = cashBalance + balanceIncrease; }
	void decreasePlayerBalance(int balanceDecrease) { if (cashBalance - balanceDecrease < 0) { throw "Not enough cash"; } else cashBalance = cashBalance - balanceDecrease; }

	// Player fuel functions
	int getPlayerFuel() { return fuelAmount; }
	void setPlayerFuel(int newFuelLevel) { fuelAmount = newFuelLevel; }
	void increaseFuel(int fuelIncrease) {fuelAmount = fuelAmount + fuelIncrease ; }
	void decreaseFuel(int fuelDecrease) { if (fuelAmount - fuelDecrease <= 0) { throw "Tank empty"; } else  fuelAmount = fuelAmount - fuelDecrease;  }



private:
	int positionX = 0; // player x position in pixels on the map
	int positionY = 0; // player y position in pixels on the map

	bool in_air;
	
	int cashBalance = 500;
	int fuelAmount = 100;

};


class Engine {

};

class Drill {

};

class fuelTankCapacity {

};


class Inventory {

};