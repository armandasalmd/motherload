#pragma once
#include "Map.h"
#include "Player.h"
//http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

class Mining {
public:
	static void mineBlock(Map *map, Player *player, int dx, int dy);
};