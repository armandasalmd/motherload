#pragma once
#include <string>


namespace {
	/* ___________________ Winfo ______________________ */
	struct Winfo {
		// window info, window settings(static)
		static const std::string title;

		static const int FPS = 60;
		static const int frameDelay = 1000 / FPS;

		static const int block_size = 64; // width and height in pixels
		static const int blocks_x = 15; // blocks vertically
		static const int blocks_y = 11; // blocks horizontally

		static const int width = blocks_x * block_size; // window width
		static const int height = blocks_y * block_size; // window height
		
		static const int x_blocks = width / block_size; // blocks shown vertically
		static const int y_blocks = height / block_size; // blocks shown horizontally

		static const bool full_screen = false;

		static const int text_size = 22;
	};

	const std::string Winfo::title = "Motherload";
	/* ________________________________________________ */

	/* ___________________ Gsettings __________________ */
	struct Gsettings {
		// Game settings
		static const int step = 4; // step size in px
		static const double gravity;
		static const double max_gravity_speed;
	};

	const double Gsettings::gravity = 0;
	const double Gsettings::max_gravity_speed = 4.8;
	/* ________________________________________________ */

}


