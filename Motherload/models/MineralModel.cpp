#include "MineralModel.h"


MineralModel::MineralModel() {
	id = 0;
	name = "undefined";
	price = 0;
	weight = 0;
}

MineralModel::MineralModel(int id, std::string name, int price, int weight) {
	this->id = id;
	this->name = name;
	this->price = price;
	this->weight = weight;
}

