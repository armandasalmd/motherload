// <summary>Instance class for every building with drawing functionality</summary>
// <author>barkausa</author>

#pragma once
#include <string>
#include "ModelObjects.h"
#include "StaticVars.h"
#include "TextureObject.h"

class BuildingObject : public TextureObject {
public:
	// __________ Constructors __________
	BuildingObject() : TextureObject("") {  };
	BuildingObject(BuildingModel model);

	// __________ Setters __________
	inline void SetPosCoords(int x, int y) { posx = x, posy = y; }
	inline void SetX(int x) { posx = x; }
	inline void SetY(int y) { posy = y; }

	// __________ Getters __________
	inline int PosX() { return posx; }
	inline int PosY() { return posy; }
	inline BuildingModel GetModel() { return mModel; }
private:
	BuildingModel mModel;	// holds building path, coords. etc.
	int posx, posy;			// absolute coords on the map
};


