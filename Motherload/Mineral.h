#ifndef Material_HEADER
#define Material_HEADER
#include <array>

class Mineral {
private:
	int x;
	int y;
	int weight;
	int health;
	int strength;
	float value;
	float frequency;
	std::string name;
public:
	Mineral() {

	}
	Mineral(std::string type) {
		std::array<int, 3> attr1 = { 3, 1, 4 }; //"SELECT weight, health, strength FROM minerals WHERE name = 'var name'";
		std::array<float, 2> attr2 = { 2.4f, 0.4f };//"SELECT value, frequency FROM minerals WHERE name = 'var name'";

		this->name = type;
		this->weight = attr1[0];
		this->health = attr1[1];
		this->strength = attr1[2];
		this->value = attr2[0];
		this->frequency = attr2[1];
	}

	int getX() { return this->x; }
	int getY() { return this->y; }
	int getWeight() { return this->weight; }
	int getHealth() { return this->health; }
	int getStrength() { return this->strength; }
	float getValue() { return this->value; }
	float getFrequency() { return this->frequency; }
	std::string getName() { return this->name; }

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

	void updateHealth(int newHealth) {
		this->health += newHealth;
	}

	~Mineral() { }
};
#endif