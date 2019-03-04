// UnitTest.cpp : Defines the entry point for the console application.
//

#pragma once
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <iostream>


#include "../Motherload/ModelObjects.h"
#include "../Motherload/Models.cpp"

#include "../Motherload/Game.cpp"
#include "../Motherload/Camera.cpp"
#include "../Motherload/Mineral.cpp"
#include "../Motherload/TextureObject.cpp"
#include "../Motherload/TextureManager.cpp"

#include "../Motherload/Player.cpp"
#include "../Motherload/Collision.cpp"
#include "../Motherload/Map.cpp"
#include "../Motherload/BuildingObject.cpp"
#include "../Motherload/BuildingManager.cpp"

TEST_CASE("tEssSTING cATCH")
{
	Map* map1 = new Map;
	UpgradeModel model = UpgradeModel(0, "cool", 69, 1.1f);
	Models *db = Models::getInstance();

	REQUIRE(db->getMineralById(0).getName() == "Sky");
	getchar();
}