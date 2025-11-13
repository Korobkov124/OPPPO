#include "Fish.h"

bool Fish::MatchObj(std::vector<std::string> command) {
	if (command[0] == "livingPlace") {
		int value = stoi(command[2]);
		if (command[1] == "==") return livingPlace == value;
		if (command[1] == "!=") return livingPlace != value;
	}

	return Animal::MatchObj(command);
}

void Fish::PrintObj() {
	std::string placeStr;
	switch (livingPlace) {
	case river:
		placeStr = "Река";
		break;
	case lake:
		placeStr = "Озеро";
		break;
	case sea:
		placeStr = "Море";
		break;
	default:
		placeStr = "Неизвестно";
		break;
	}
	std::cout << "Имя: " << name << " Место обитания: " << placeStr << std::endl;
}

void Fish::AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array) {
	Fish* currentFish = new Fish;
	currentFish->name = tokens[0];

	if (stoi(tokens[1]) >= Fish::river &&
		stoi(tokens[1]) <= Fish::sea) {
		currentFish->livingPlace = static_cast<Fish::placeEnum>(stoi(tokens[1]));
		array.push_back(currentFish);
		return;
	}
	else {
		throw std::invalid_argument("Неправильное значение места обитания рыбы " + tokens[0] + "!\n");
		return;
	}
}