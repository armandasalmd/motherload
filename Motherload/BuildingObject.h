#pragma once
#include <string>
#include "ModelObjects.h"
#include "StaticVars.h"
#include "TextureObject.h"

// summary:
//		Instance class for every building with drawing functionality
// author:
//		barkausa
class BuildingObject : public TextureObject {
public:
	// --------------- Constructors --------------
	BuildingObject() : TextureObject("") {  };
	BuildingObject(BuildingModel model);

	// ----------------- Setters --------------
	inline void SetPosCoords(int x, int y) { posx = x, posy = y; }
	inline void SetX(int x) { posx = x; }
	inline void SetY(int y) { posy = y; }

	// ----------------- Getters --------------
	inline int PosX() { return posx; }
	inline int PosY() { return posy; }
	inline BuildingModel GetModel() { return mModel; }
private:
	BuildingModel mModel;	// holds building path, coords. etc.
	int posx, posy;			// absolute coords on the map
};


