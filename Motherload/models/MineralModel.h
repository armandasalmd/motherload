#include <string>


class MineralModel {
public:
	MineralModel();
	MineralModel(int id, std::string name, int price, int weight);

	// Setters
	int getId() { return id; }
	std::string getName() { return name; }
	int getPrice() { return price; }
	int getWeight() { return weight; }
	float getFrequency() { return frequency; }
	int getStrength() { return strength; }

	// Getters
	void setId(int value) { id = value; }
	void setName(std::string value) { name = value; }
	void setPrice(int value) { price = value; }
	void setWeight(int value) { weight = value; }
	void setFrequency(int value) { frequency = value; }
	void setStrength(int value) { strength = value; }

private:
	int id;
	std::string name;
	int price;
	int weight;
	float frequency;
	int strength;
	// std::string texture_path;
};