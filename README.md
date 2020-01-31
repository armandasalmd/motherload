## C++ game - Motherload clone

[Original game at miniclips](https://www.miniclip.com/games/motherload/en/)


<dl>
  <dt>
    Idea:
  </dt>
  <dd>
    Mine caves, dig minerals, sell them, upgrade your mining machine. The deeper you dig, the more expensive minerals you can find.
  </dd>
  <dt>
    Requirements:
  </dt>
  <dd>
   Form a team and work using Agile, Testing. Use sqlite3 database to store normalized data
  </dd>
   <dt>
    Result:
  </dt>
  <dd>
    The game mechanics/rendering engine is fully working, database is working and tested. The project was not finished due to low contribution of some teammates (university)
  </dd>
</dl>

Game project built with primitive C++ library - SDL2. As a university module project it was **assessed: 93%**

**Tools used:** Visual Studio 2019, Sqlite3, SDL2
___
#### What have I learned?
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

___

#### Sample view
![image cant be found](https://i.gyazo.com/98f5b6b6d4f818fc6edacc9c121628c1.png)

#### Installation
All libraries are linked through relative pathing. Therefore, you don't need to install anything.
* Make sure you have Windows SDK installed!
* Clone it
* *You might need to retarget the project (change SDK version)
* Ctrl + F5 (run)


##### SQLite3 installation (Windows):
1. Start Menu-> Visual Studio 2017 -> Developer CMD
2. [Follow the tutorial](https://cppcodetips.wordpress.com/tag/including-sqlite-with-visual-studio/)
3. Last command line should be: lib /def:sqlite3.def /out:sqlite3.lib /machine:X64
