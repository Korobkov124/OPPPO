#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

//Исходное содержание текстового файла
//ADD Fish Karp 0
//ADD Fish Skopa 2
//ADD Bird Skopa 3.2
//ADD Bird Eagle 10.5
//ADD Insect Bug 5 10.03.1900
//ADD Insect Skopa 3 12.01.1890
//REM name == 'Scopa'
//PRINT

int parseDate(const std::string& date) {
	int day = std::stoi(date.substr(0, 2));
	int month = std::stoi(date.substr(3, 2));
	int year = std::stoi(date.substr(6, 4));
	return year * 10000 + month * 100 + day;
}

class Animal { //TODO: Рефакторинг классов на заголовочные файлы, по феншую!
public:
	string name;

	static void AddToArray(vector<string>& tokens, vector<Animal*>& array);

	static void DelObj(vector<string> tokens, vector<Animal*>& array);

	virtual bool MatchObj(vector<string> command);

	virtual void PrintObj();

	static void PrintArray(vector<Animal*> array);
};

class Fish : public Animal {
public:
	enum placeEnum {
		placeEnumDefault = 0,
		river = 1,
		lake = 2,
		sea = 3
	};

	placeEnum livingPlace = placeEnumDefault;

	void PrintObj() override;

	bool MatchObj(vector<string> command) override;
};

class Bird : public Animal {
public:
	float fast = 0;

	void PrintObj() override;

	bool MatchObj(vector<string> command) override;
};

class Insect : public Animal {
public:
	float size = 0;

	string dateOfOpening;

	void PrintObj() override;

	bool MatchObj(vector<string> command) override;
};

void Animal::AddToArray(vector<string>& tokens, vector<Animal*>& array) {

	if (tokens[1] == "Fish" && tokens.size() == 4) {
		Fish* currentFish = new Fish;
		currentFish->name = tokens[2];

		if (stoi(tokens[3]) >= Fish::river &&
			stoi(tokens[3]) <= Fish::sea) {
			currentFish->livingPlace = static_cast<Fish::placeEnum>(stoi(tokens[3]));
			array.push_back(currentFish);
			return;
		}
		else {
			throw string("Неправильное значение места обитания рыбы " + tokens[2] + "!\n");
			return;
		}
	}

	else if (tokens[1] == "Bird" && tokens.size() == 4) {
		Bird* currentBird = new Bird;
		currentBird->name = tokens[2];

		if (stof(tokens[3]) > 0) {
			currentBird->fast = stof(tokens[3]);
			array.push_back(currentBird);
			return;
		}
		else {
			throw string("Неправильное значение скорости птицы " + tokens[2] + "!\n");
			return;
		}

	}

	else if (tokens[1] == "Insect" && tokens.size() == 5) {
		Insect* currentInsect = new Insect;
		currentInsect->name = tokens[2];

		if (stoi(tokens[3]) >= 0) {
			currentInsect->size = stof(tokens[3]);
			currentInsect->dateOfOpening = tokens[4];
			array.push_back(currentInsect);
			return;
		}
		else {
			throw string("Неправильное значение размера жука " + tokens[2] + "!\n");
			return;
		}
	}
	else {
		throw string("Неправильная строка!\n");
		return;
	}
}

void Animal::DelObj(vector<string> command, vector<Animal*>& array) {
	array.erase(
		remove_if(array.begin(), array.end(),
			[&](Animal* obj) {
				return obj->MatchObj(command);
			}),
		array.end()
	);
}

bool Animal::MatchObj(vector<string> command) {
	if (command[1] == "name") {
		string value = command[3];
		if (command[2] == "==") return name == value;
		if (command[2] == "!=") return name != value;
	}

	return false;
}

bool Fish::MatchObj(vector<string> command) {
	if (command[1] == "livingPlace") {
		int value = stoi(command[3]);
		if (command[2] == "==") return livingPlace == value;
		if (command[2] == "!=") return livingPlace != value;
	}

	return Animal::MatchObj(command);
}

bool Bird::MatchObj(vector<string> command) {
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

bool Insect::MatchObj(vector<string> command) {
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
		int valueDate = parseDate(command[3]);
		int valueOwnDate = parseDate(dateOfOpening);
		if (command[2] == "==") return valueOwnDate == valueDate;
		if (command[2] == "!=") return valueOwnDate != valueDate;
		if (command[2] == ">") return valueOwnDate > valueDate;
		if (command[2] == "<") return valueOwnDate < valueDate;
		if (command[2] == ">=") return valueOwnDate >= valueDate;
		if (command[2] == "<=") return valueOwnDate <= valueDate;
	}

	return Animal::MatchObj(command);
}

void Animal::PrintObj() {
	cout << "Имя: " << name << endl;
}


void Fish::PrintObj() {
	string placeStr;
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
	cout << "Имя: " << name << " Место обитания: " << placeStr << endl;
}

void Bird::PrintObj() {
	cout << "Имя: " << name << " Скорость полета: " << fast << "м/с" << endl;
}
	
void Insect::PrintObj() {
	cout << "Имя: " << name << " Размер: " << size << "см^2" << " Дата открытия: " << dateOfOpening << endl;
}

void Animal::PrintArray(vector<Animal*> array)
{
	cout << "---------- Вывод элементов контейнера в консоль ----------\n";
	for (int i = 0; i < array.size(); i++) {
		array[i]->PrintObj();
	}
}

static vector<string> splitString(const string& str, char delimiter) {
	vector<string> tokens;
	string token;
	istringstream tokenStream(str);

	while (getline(tokenStream, token, delimiter)) {

		if (!token.empty()) {
			tokens.push_back(token);
		}
	}

	return tokens;
}

void ParseTxt() {
	string currentLine;
	ifstream iftxt("parsed.txt");
	int lineCount = 0;
	vector<Animal*> array;

	if (iftxt.is_open()) {

		while(getline(iftxt, currentLine)) {
			lineCount++;
			cout << "Команда " << lineCount << ": " << currentLine << endl;
			vector<string> tokens = splitString(currentLine, ' ');

			if (tokens.empty()) continue;

			if (tokens[0] == "ADD") {
				Animal::AddToArray(tokens, array);
			}

			if (tokens[0] == "REM") {
				Animal::DelObj(tokens, array);
			}

			if (tokens[0] == "PRINT") {
				Animal::PrintArray(array);
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	
	cout << "Парсинг текстовых команд из файла с расширением .txt" << endl;
	ParseTxt();

	return 0;
}