#pragma once
#include "Mining.h"

void Mining::mineBlock(Map *map, Player *player, int nextX, int nextY) {

	auto currentMap = map->GetMap();
	Mineral mineral = currentMap[nextY][nextX];

	//if (player->getStrength() >= mineral.getStrength() && mineral.getName() != "sky")
	if (mineral.getName() != "sky")
	{

		if (mineral.getHealth() <= 0)
		{
			//Increase player pos by a little amount towards the new block
			Mineral newMin("sky");
			map->GetMap().at(nextY).at(nextX) = newMin;
		}
		else
		{
			//if (player.getInventory() - mineral.getWeight() >= 0)			//Check inventory space  
			//{				
			/*----------------http://www.cplusplus.com/reference/thread/this_thread/sleep_for/---------------*/
			std::this_thread::sleep_for(std::chrono::seconds(1));  //At this point there should be an animation

			map->GetMap().at(nextY).at(nextX).updateHealth(-1);//-player->getStrength());		//Decrease 'health' of block being mined

			//player.updateInventory(mineral.getValue(), mineral.getWeight());		//Update player inventory and weight taken by mineral
			//}
		}

	}
}