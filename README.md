##Motherload
Game project built with primitive C++ library - SDL2. As a university module project it was assessed: 93%

**Tools used:** Visual Studio 2019, Sqlite3, SDL2
___
### What have I learned?
* Debugging
* Unit testing
* OOP, polymorphism, encapsulation
* ``static``, ``abstract``, ``friend`` usage
* Proper code commenting
* Linking external libraries using "relative path"
* SQL query skills
* Database normalization
* Entity Relationship Diagram (``ERD``)
* Many many pointers and reference variables!
* Iterable containers such as ``vector<>``
* SDL2 library
* Critical thinking while building a game engine!

### Sample view
![image cant be found](https://i.gyazo.com/98f5b6b6d4f818fc6edacc9c121628c1.png)

### Installation
All libraries are linked through relative pathing. Therefore, you don't need to install anything.
* Make sure you have Windows SDK installed!
* Clone it
* *You might need to retarget the project (change SDK version)
* Ctrl + F5 (run)

##### There are some tutorials in case you need them:
[SDL2 installation](https://www.youtube.com/watch?v=QQzAHcojEKg)

[Sqlite DOCS - tutorialspoint](https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm)

##### SQLite3 installation (Windows):
1. Start Menu-> Visual Studio 2017 -> Developer CMD
2. [Follow the tutorial](https://cppcodetips.wordpress.com/tag/including-sqlite-with-visual-studio/)
3. Last command line should be: lib /def:sqlite3.def /out:sqlite3.lib /machine:X64

___

### My Commenting Rules (by barkausa): 

* To capture new tasks write: 
```c++
// TODO(user): do some feature
```

* For consistency, every line comment is above that line:
```c++
// Getting database controller
Models::getInstance();
```


* Sometimes if code is short enough you can align multiple line comments
```c++
game->handleEvents();		// handle any user input
game->update();			// update all objects eg. positions etc.
game->render(fps);		// render changes to the display
```

* Every file has main author at the top and explanation of it `(collaborators are exceptional)`:
main.cpp:
```xml
/*
	summary:
		startup file, counts fps, runs main loop</summary>
	author:
		barkausa
 	collab:
		waheedi
*/
```

* Every function description must be above its head in .h `(if possible)` file:
	* Function can be described using those as tags:
		* summary - description of the function
		* remarks - additional comments
		* param - description about parameters
		* example - if needed give an example
		* returns - describes what function returns
```xml
// summary:
// 	Function mines a block, notifies inventory to add mineral
// remarks:
// 	Function frozes a little bit the program (can be improved)
// param:
//	map:
//		Current drawable map
//	player:
//		Current player map
//	dx:
//		Minable block x
//	dy:
//		Mineble block y
static void mineBlock(Map *map, Player *player, int dx, int dy);
```

##### In class Function block commenting (example)
```c++
class Player: public TextureObject {
public:
	// __________ Constructors __________
	Player(const char *path) : TextureObject(path) {}
	Player(const char *path, int x, int y, bool anim) : TextureObject(path, x, y, anim) {}
	
	// __________ Getters ___________
	// Player pixel coordinates
	int PosX() { return positionX; }
	int PosY() { return positionY; }
	bool IsInAir() { return in_air; }
	
	// __________ Player Movement __________
	// Move player pixel coordinates around the map
	void DeltaCoords(int dx, int dy) { SetCoords(positionX + dx, positionY + dy); }
	void DeltaX(int dx) { SetCoords(positionX + dx, positionY); }
	void DeltaY(int dy) { SetCoords(positionX, positionY + dy); }
}
```

