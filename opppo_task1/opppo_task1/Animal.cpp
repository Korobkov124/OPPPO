#include "Animal.h"
#include "Fish.h"
#include "Bird.h"
#include "Insect.h"

void Animal::AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array) {
	if (tokens[0] == "Fish" && tokens.size() == 3) {
		tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
		Fish::AddToArray(tokens, array);
		return;
	}

	else if (tokens[0] == "Bird" && tokens.size() == 3) {
		tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
		Bird::AddToArray(tokens, array);
		return;
	}

	else if (tokens[0] == "Insect" && tokens.size() == 4) {
		tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
		Insect::AddToArray(tokens, array);
		return;
	}
	else{
		throw std::invalid_argument("Некорректное название типа!");
	}
}

void Animal::DelObj(std::vector<std::string> command, std::vector<Animal*>& array) {
	array.erase(
		remove_if(array.begin(), array.end(),
			[&](Animal* obj) {
				return obj->MatchObj(command);
			}),
		array.end()
	);
}

bool Animal::MatchObj(std::vector<std::string> command) {
	if (command[0] == "name") {
		std::string value = command[2];
		if (command[1] == "==") return name == value;
		if (command[1] == "!=") return name != value;
	}

	return false;
}

void Animal::PrintObj() {
	std::cout << "Имя: " << name << std::endl;
}

void Animal::PrintArray(std::vector<Animal*> array)
{
	std::cout << "---------- Вывод элементов контейнера в консоль ----------\n";
	for (int i = 0; i < array.size(); i++) {
		array[i]->PrintObj();
	}
}