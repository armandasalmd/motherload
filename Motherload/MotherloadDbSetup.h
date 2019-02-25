#pragma once
#include <iostream>

int main()
{
	sqlite::sqlite db(MotherloadDB.sqlite);			
	auto cur = db.get_statement();

}

int insertBackpackData()
{
	sqlite::sqlite db(MotherloadDB.sqlite);
	auto cur = db.get_statement();

	cur->set_sql(  "INSERT INTO Backpack"
					"VALUES (?, ?);"  );
	
	cur->prepare();

	cur->bind(1, 6);
	cur->bind(2, 12);
	cur->bind(3, 18);
	cur->bind(4, 24);
	cur->bind(5, 30);
	
	cur->step();		
}

int insertDrillData()
{
	sqlite::sqlite db(MotherloadDB.sqlite);
	auto cur = db.get_statement();

	cur->set_sql("INSERT INTO Drill"
		"VALUES (?, ?);");

	cur->prepare();

	cur->bind(1, 5);
	cur->bind(2, 10);
	cur->bind(3, 15);
	cur->bind(4, 20);
	cur->bind(5, 25);

	cur->step();
}

int insertMineralData()
{
	sqlite::sqlite db(MotherloadDB.sqlite);
	auto cur = db.get_statement();

	cur->set_sql("INSERT INTO Mineral"
		"VALUES (?, ?, ?, ?, ?, ?, ?, ?);");

	cur->prepare();

	cur->bind(0,	"Grass",	0.25,	1,		3,	0,	6,		"assets/grass.png");	
	cur->bind(1,	"Dirt",		0.25,	1,		3,	3,	6,		"assets/dirt.png");		
	cur->bind(2,	"Stone",	2,		2,		5,	15,	15,		"assets/stone.png");	
	cur->bind(3,	"Bronze",	5,		3,		8,	10,	20,		"assets/bronze.png");
	cur->bind(4,	"Silver",	20,		5,		10,	10,	25,		"assets/silver.png");
	cur->bind(5,	"Iron",		50,		10,		12,	10,	30,		"assets/iron.png");
	cur->bind(6,	"Gold",		200,	20,		15,	10,	50,		"assets/gold.png");
	cur->bind(7,	"Ruby",		500,	50,		18,	5,	70,		"assets/ruby.png");
	cur->bind(8,	"Emerald",	1500,	100,	20,	5,	90,		"assets/emerald.png");
	cur->bind(9,	"Diamond",	5000,	250,	25,	5,	120,	"assets/diamond.png");
	cur->bind(10,	"Water",	0,		0,		0,	0,	0,		"assets/water.png");

	cur->step();
}