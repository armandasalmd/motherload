#pragma once
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <string>
#include <vector>

#include "../Motherload/BuildingObject.cpp"
#include "../Motherload/BuildingManager.cpp"
#include "../Motherload/ModelObjects.cpp"
#include "../Motherload/Models.cpp"

#include "../Motherload/Mining.cpp"
#include "../Motherload/Game.cpp"
#include "../Motherload/Camera.cpp"
#include "../Motherload/Mineral.cpp"
#include "../Motherload/TextureObject.cpp"
#include "../Motherload/TextureManager.cpp"
#include "../Motherload/Player.cpp"
#include "../Motherload/Collision.cpp"
#include "../Motherload/Map.cpp"

TEST_CASE("Database/Models Inventory model in player model") {
	PlayerModel pModel = Models::getInstance()->getPlayerById(2);
	std::vector<InventoryItemModel> pInventory = Models::getInstance()->getInventoryById(2);
	if (pInventory.size() != 0 && pModel.getInventory()->size() != 0) {
		REQUIRE((*pModel.getInventory())[0].getMineralId() == pInventory[0].getMineralId());
		REQUIRE((*pModel.getInventory())[0].getQuantity() == pInventory[0].getQuantity());
	}
	REQUIRE(pModel.getInventory()->size() == pInventory.size());
}

TEST_CASE("Get data from database")
{
	Models *db = Models::getInstance();

	WHEN ("Pulling upgrades") {
		std::string tables[] = { "FuelTank", "Backpack", "Engine", "Hull", "Drill" };
		int first_4_prices[] = {0, 750, 2000, 5000, 20000, 120000};
		UpgradeModel model;
		for (int i = 0; i < 5; i++) {
			// iterates 4 prices - all the same for all upgrades except last one!
			for (int j = 0; j < 4; j++) { 
				model = db->getUpgradeById(tables[i], j);
				REQUIRE(model.getPrice() == first_4_prices[j]);
			}			
		}
	}

	WHEN("Pulling minerals") {
		int n = 11;
		int frequency[] = { 0,0,84,86,88,90,92,94,96,98,100 };
		std::string folder = "assets/";
		std::string names[] = { "sky", "grass", "dirt", "stone", "bronze", "silver", "iron", "gold", "ruby", "emerald", "diamond" };
		MineralModel model;
		for (int i = 0; i < n; i++) {
			model = db->getMineralById(i);
			REQUIRE(frequency[i] == model.getFrequency());
			REQUIRE(folder + names[i] + ".png" == model.getTexturePath());
			names[i][0] = toupper(names[i][0]); // Names starts with an upper case
			REQUIRE(names[i] == model.getName());
		}
	}

	WHEN("Pulling sample player 1") {
		PlayerModel model = db->getPlayerById(1);
		std::string player_name = "DefaultUser12";
		REQUIRE(model.getPlayerName() == player_name);
		REQUIRE(model.getHealth() == 100);
		REQUIRE(model.getUpgrade("backpack_level") == 0);
		REQUIRE(model.getUpgrade("drill") == 0);
		REQUIRE(model.getMapJson() == "[]");
	}

	WHEN("Pulling sample player 2") {
		PlayerModel model = db->getPlayerById(2);
		std::string player_name = "BestTeam7";
		REQUIRE(model.getPlayerName() == player_name);
		REQUIRE(model.getHealth() == 85);
		REQUIRE(model.getUpgrade("engine") == 1);
		REQUIRE(model.getUpgrade("drill") == 2);
	}

	WHEN("Pulling Inventory") {
		std::vector<InventoryItemModel> model = db->getInventoryById(2);
		REQUIRE(model.size() == 4);
		for (int i = 0; i < 4; i++) {
			REQUIRE((model[i].getMineralId() >= 3 || model[i].getMineralId() <= 10));
			REQUIRE(model[i].getQuantity() > 0);
		}
	}

	//getchar();
}

TEST_CASE("Buildings detection") {
	Game *game = new Game();
	Player *p = new Player("assets/player.png", 0, 0, false);


	WHEN("Gas Station") {
		p->SetCoords(220, 256);
		Collision::DetectBuildingCollision(game, p);
		REQUIRE(game->getState() == State::GasStation);
	}

	WHEN("Market") {
		p->SetCoords(716, 261);
		Collision::DetectBuildingCollision(game, p);
		REQUIRE(game->getState() == State::Market);
	}

	WHEN("Shop") {
		p->SetCoords(1232, 258);
		Collision::DetectBuildingCollision(game, p);
		REQUIRE(game->getState() == State::UpgradesShop);
	}

	WHEN("Save flag") {
		p->SetCoords(1664, 256);
		Collision::DetectBuildingCollision(game, p);
		REQUIRE(game->getState() == State::Save);
	}

	delete game;
	delete player;
}