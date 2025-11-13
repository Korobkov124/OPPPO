#include "Insect.h"

bool Insect::MatchObj(std::vector<std::string> command) {
	if (command[1] == "size") {
		int value = stoi(command[3]);
		if (command[2] == "==") return size == value;
		if (command[2] == "!=") return size != value;
		if (command[2] == ">") return size > value;
		if (command[2] == "<") return size < value;
		if (command[2] == ">=") return size >= value;
		if (command[2] == "<=") return size <= value;
	}
	else if (command[1] == "dateOfOpening") {
		int valueDate = Parser::parseDate(command[3]);
		int valueOwnDate = Parser::parseDate(dateOfOpening);
		if (command[2] == "==") return valueOwnDate == valueDate;
		if (command[2] == "!=") return valueOwnDate != valueDate;
		if (command[2] == ">") return valueOwnDate > valueDate;
		if (command[2] == "<") return valueOwnDate < valueDate;
		if (command[2] == ">=") return valueOwnDate >= valueDate;
		if (command[2] == "<=") return valueOwnDate <= valueDate;
	}

	return Animal::MatchObj(command);
}

void Insect::PrintObj() {
	std::cout << "Имя: " << name << " Размер: " << size << "см^2" << " Дата открытия: " << dateOfOpening << std::endl;
}

void Insect::AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array) {
	Insect* currentInsect = new Insect;
	currentInsect->name = tokens[2];

	if (stoi(tokens[3]) >= 0) {
		currentInsect->size = stof(tokens[3]);
		currentInsect->dateOfOpening = tokens[4];
		array.push_back(currentInsect);
		return;
	}
	else {
		throw std::string("Неправильное значение размера жука " + tokens[2] + "!\n");
		return;
	}
}