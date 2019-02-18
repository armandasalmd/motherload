CREATE TABLE Player(
	playerID			varchar	PRIMARY KEY,
	drillLevel			varchar,
	backpackLevel		varchar,
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

INSERT INTO Minerals
VALUES
	(0,		"Grass",	0.25,	1,	3,	0,	6,	"assets/grass.png"),
	(1,		"Dirt",		0.25,	1,	3,	3,	6,	"assets/dirt.png"),
	(2,		"Stone",	2,		2,	5,	15,	15,	"assets/stone.png"),
	(3,		"Bronze",	5,		3,	8,	10,	20,	"assets/bronze.png"),
	(4,		"Silver",	20,		5,	10,	10,	25,	"assets/silver.png"),
	(5,		"Iron",		50,		10,	12,	10,	30,	"assets/iron.png");
