// <summary>Constant values stored in one file - game settings</summary>
// <author>barkausa</author>

#pragma once
#include <string>

namespace {
	enum BlockList { SKY = 0, GRASS, DIRT, STONE, BRONZE, SILVER, IRON, GOLD, RUBY, EMERALD, DIAMOND };
	struct Coord { int x = 0, y = 0; };

	/* __________ Window parameters __________ */
	struct Winfo {
		// window info, window settings(static)
		static const std::string title;
		static const std::string db_name;

		static const int FPS = 30;
		static const int frameDelay = 1000 / FPS;

		static const int block_size = 64; // width and height in pixels
		static const int blocks_x = 15; // blocks vertically
		static const int blocks_y = 11; // blocks horizontally

		static const int width = blocks_x * block_size; // window width
		static const int height = blocks_y * block_size; // window height
		
		static const int x_blocks = width / block_size; // blocks shown vertically
		static const int y_blocks = height / block_size; // blocks shown horizontally

		static const bool full_screen = false;

		static const int text_size = 22; // default text size
	};

	const std::string Winfo::title = "Motherload";
	const std::string Winfo::db_name = "game.sqlite";

	/* __________ Game settings __________ */
	struct Gsettings {
		static const int spawn_x = 7;
		static const int spawn_y = 3;

		static const int step = 4;		// step size in px
		static const double gravity;
		static const double max_gravity_speed;
	};

	const double Gsettings::gravity = 0.8;
	const double Gsettings::max_gravity_speed = 8.0;

	/* __________ World/Map info __________ */
	struct WorldInfo {
		// measures in blocks
		static const int b_sky_height = 5;
		static const int b_world_width = 28;
		static const int b_world_height = 128;
		// measures in px
		static const int world_width = b_world_width * Winfo::block_size;
		static const int world_height = b_world_height * Winfo::block_size;
	};
}