#include "Bird.h"

bool Bird::MatchObj(std::vector<std::string> command) {
	if (command[1] == "fast") {
		int value = stoi(command[3]);
		if (command[2] == "==") return fast == value;
		if (command[2] == "!=") return fast != value;
		if (command[2] == ">") return fast > value;
		if (command[2] == "<") return fast < value;
		if (command[2] == ">=") return fast >= value;
		if (command[2] == "<=") return fast <= value;
	}

	return Animal::MatchObj(command);
}

void Bird::PrintObj() {
	std::cout << "Имя: " << name << " Скорость полета: " << fast << "м/с" << std::endl;
}

void Bird::AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array) {
	Bird* currentBird = new Bird;
	currentBird->name = tokens[2];

	if (stof(tokens[3]) > 0) {
		currentBird->fast = stof(tokens[3]);
		array.push_back(currentBird);
		return;
	}
	else {
		throw std::string("Неправильное значение скорости птицы " + tokens[2] + "!\n");
		return;
	}
}