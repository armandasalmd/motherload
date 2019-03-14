# Recommended Commenting Rules (by barkausa): 
[Microsoft docs](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/xmldoc/summary)

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
<summary>startup file, counts fps, runs main loop</summary>
<author>barkausa</author>
<collab>waheedi</collab>
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
// <sumarry>
// Function mines a block, notifies inventory to add mineral
// </summary>
// <remarks>
// Function frozes a little bit the program (can be improved)
// </remarks>
// <param name="map">Current drawable map</param>
// <param name="player">Current player map</param>
// <param name="dx">Minable block x</param>
// <param name="dy">Minable block y</param>
static void mineBlock(Map *map, Player *player, int dx, int dy);
```

# Installation
All libraries are linked through relative pathing. Therefore, you don't need to install anything.
* Make sure you have Windows SDK installed
* Clone it
* Ctrl + F5 (run)

##### There are some tutorials in case you need them:
[SDL2 installation](https://www.youtube.com/watch?v=QQzAHcojEKg)

[Sqlite DOCS - tutorialspoint](https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm)

[Menu GUI interface (SDL based/ 32bit)](https://github.com/killerrin/SDL-GUI-API)

[Menu GUI interface 2](https://gamedev.stackexchange.com/questions/151458/sdl2-gui-same-window)

##### SQLite3 installation (Windows):
1. Start Menu-> Visual Studio 2017 -> Developer CMD
2. [Follow the tutorial](https://cppcodetips.wordpress.com/tag/including-sqlite-with-visual-studio/)
3. Last command line should be: lib /def:sqlite3.def /out:sqlite3.lib /machine:X64
