CREATE TABLE Player(
	playerID			varchar	PRIMARY KEY,
	drillLevel			varchar	DEFAULT 1,
	backpackLevel		varchar	DEFAULT 1,
	FOREIGN KEY(drillLevel)		REFERENCES Drill(drillLevel),
	FOREIGN KEY(backpackLevel)	REFERENCES Backpack(backpackLevel)
);

CREATE TABLE Backpack(
	backpackLevel		varchar PRIMARY KEY,
	backpackCapacity	varchar
);

CREATE TABLE Drill(
	drillLevel			varchar PRIMARY KEY,
	drillStrength		varchar
);

CREATE TABLE hasMinerals(
	playerID			varchar,
	mineralID			varchar,
	mineralQuantity		varchar
	FOREIGN KEY(playerID)		REFERENCES Player(playerID),
	FOREIGN KEY(mineralID)		REFERENCES Minerals(mineralID),
	PRIMARY KEY(playerID, mineralID)		
);

CREATE TABLE Minerals(
	mineralID			varchar	PRIMARY KEY,
	mineralName			varchar,
	mineralValue		decimal(7,2),
	mineralWeight		varchar,
	mineralStrength		varchar,
	mineralFrequency	varchar,
	mineralHealth		varchar,
	texturePath			nvarchar(260)
);

INSERT INTO Backpack 
VALUES
	(1, 6),
	(2, 12),
	(3, 18),
	(4, 24),
	(5, 30);

INSERT INTO Drill
VALUES
	(1, 5),
	(2, 10),
	(3, 15),
	(4, 20),
	(5, 25);

INSERT INTO Mineral
VALUES
	(0,		"Grass",	0.25,	1,		3,	0,	6,		"assets/grass.png"),
	(1,		"Dirt",		0.25,	1,		3,	3,	6,		"assets/dirt.png"),
	(2,		"Stone",	2,		2,		5,	15,	15,		"assets/stone.png"),
	(3,		"Bronze",	5,		3,		8,	10,	20,		"assets/bronze.png"),
	(4,		"Silver",	20,		5,		10,	10,	25,		"assets/silver.png"),
	(5,		"Iron",		50,		10,		12,	10,	30,		"assets/iron.png"),
	(6,		"Gold",		200,	20,		15,	10,	50,		"assets/gold.png"),
	(7,		"Ruby",		500,	50,		18,	5,	70,		"assets/ruby.png"),
	(8,		"Emerald",	1500,	100,	20,	5,	90,		"assets/emerald.png"),
	(9,		"Diamond",	5000,	250,	25,	5,	120,	"assets/diamond.png"),
	(10,	"Water",	0,		0,		0,	0,	0,		"assets/water.png");


	/* The following to be used within the C++ code as part of functions */

UPDATE Player
SET drillLevel = newDrillLevel
WHERE playerID = currentPlayerID;

UPDATE Player
SET backpackLevel = newBackpackLevel
WHERE playerID = currentPlayerID;

UPDATE hasMinerals
SET mineralQuantity = newQuantity
WHERE playerID = currentPlayerID AND mineralID = mineralToUpdate;