#include "Animal.h"
#include "Fish.h"
#include "Bird.h"
#include "Insect.h"

void Animal::AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array) {

	if (tokens[1] == "Fish" && tokens.size() == 4) {
		Fish::AddToArray(tokens, array);
		return;
	}

	else if (tokens[1] == "Bird" && tokens.size() == 4) {
		Bird::AddToArray(tokens, array);
		return;
	}

	else if (tokens[1] == "Insect" && tokens.size() == 5) {
		Insect::AddToArray(tokens, array);
		return;
	}
	else {
		throw std::string("Неправильная строка!\n");
		return;
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
	if (command[1] == "name") {
		std::string value = command[3];
		if (command[2] == "==") return name == value;
		if (command[2] == "!=") return name != value;
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
