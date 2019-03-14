// <summary>Class holds main info about object drawing(size, coordinates...)</summary>
// <remarks>This class is parent(inherited) for Player, Block, Building objects </remarks>
// <author>barkausa</author>

#pragma once
#include "Game.h"
#include "StaticVars.h"

class TextureObject {
public:
	// __________ Constructors __________
	TextureObject(const char *path, int x, int y, bool anim);
	TextureObject(const char *path);

	// __________ Setters __________
	void SetDrawCoords(const int x, const int y);
	void SetOffset(const int dx, const int dy);		// shift camera
	void SetDimentions(const int w, const int h);	// set object width, height

	// __________ Getters __________
	int getX();
	int getY();
	
	// __________ Render funcs __________
	void Update();
	void Render();
	
	// __________ Texture manipulation __________
	void Move(const int dx, const int dy);			// moves texture on the screen
	void DeltaOffset(const int dx, const int dy);	// move offset
	void ChangeTexture(const char *path);
protected:
	int mx = 0;			// Drawing on the screen x(px)
	int my = 0;			// Drawing on the screen y(px)
	int width = Winfo::block_size;
	int height = Winfo::block_size;
	int offsetX = 0;	// camera offset
	int offsetY = 0;	// camera offset

	// <remarks>implemented(working) but not used for now
	bool animated = false;
	int anim_speed = 250;
	int anim_frames = 4;
	// </remarks>

	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;
};