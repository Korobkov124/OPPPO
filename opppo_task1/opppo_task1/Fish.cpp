#include "Fish.h"

bool Fish::MatchObj(std::vector<std::string> command) {
	if (command[1] == "livingPlace") {
		int value = stoi(command[3]);
		if (command[2] == "==") return livingPlace == value;
		if (command[2] == "!=") return livingPlace != value;
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
	currentFish->name = tokens[2];

	if (stoi(tokens[3]) >= Fish::river &&
		stoi(tokens[3]) <= Fish::sea) {
		currentFish->livingPlace = static_cast<Fish::placeEnum>(stoi(tokens[3]));
		array.push_back(currentFish);
		return;
	}
	else {
		throw std::string("Неправильное значение места обитания рыбы " + tokens[2] + "!\n");
		return;
	}
}