#include "Bird.h"

bool Bird::MatchObj(std::vector<std::string> command) {
	if (command[0] == "fast") {
		float value = stof(command[2]);
		if (command[1] == "==") return fast == value;
		if (command[1] == "!=") return fast != value;
		if (command[1] == ">") return fast > value;
		if (command[1] == "<") return fast < value;
		if (command[1] == ">=") return fast >= value;
		if (command[1] == "<=") return fast <= value;
	}

	return Animal::MatchObj(command);
}

void Bird::PrintObj() {
	std::cout << "Имя: " << name << " Скорость полета: " << fast << "м/с" << std::endl;
}

void Bird::AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array) {
	auto currentBird = std::make_unique<Bird>();
	currentBird->name = tokens[0];

	if (stof(tokens[1]) > 0) {
		currentBird->fast = stof(tokens[1]);
		array.push_back(std::move(currentBird));
		return;
	}
	else {
		throw std::invalid_argument("Неправильное значение скорости птицы " + tokens[0] + "!\n");
		return;
	}
}