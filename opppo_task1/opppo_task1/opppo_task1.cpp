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

class Animal { //TODO: Рефакторинг классов на заголовочные файлы, по феншую!
public:
	string name;

	static void AddToArray(vector<string> tokens, vector<Animal*>& array);

	static void DelObjs(vector<string> command, vector<Animal*> array);

	virtual void PrintObj();

	static void PrintArray(vector<Animal*> array);
};

class Fish : public Animal {
public:
	enum placeEnum {
		river = 0,
		lake = 1,
		sea = 2
	};

	placeEnum livingPlace;

	void PrintObj() override;
};

class Bird : public Animal {
public:
	float fast = 0;

	void PrintObj() override;
};

class Insect : public Animal {
public:
	float size = 0;

	string dateOfOpening;

	void PrintObj() override;
};

void Animal::AddToArray(vector<string> tokens, vector<Animal*>& array) {

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

void Animal::DelObjs(vector<string> command, vector<Animal*> array) {
	if (command.size() == 4) {
		if (command[2] == "==") { //TODO: Сделай общую функцию del внутри базового класса Animal,
			                      //      а потом перегрузи в дочерних классах по полям!
		}
		if (command[2] == "!=") {

		}
		if (command[2] == "<") {

		}
		if (command[2] == ">") {

		}
		if (command[2] == "<=") {

		}
		if (command[2] == ">=") {

		}
	}
	else {
		throw string("Неправильная строка!\n");
		return;
	}
}

void Animal::PrintObj() {
	cout << "Имя: " << name << endl;
}

void Fish::PrintObj(){
	cout << "Имя: " << name << " Место обитания: " << livingPlace << endl;
}

void Bird::PrintObj() {
	cout << "Имя: " << name << " Скорость полета: " << fast << endl;
}
	
void Insect::PrintObj() {
	cout << "Имя: " << name << " Размер: " << size << " Дата открытия: " << dateOfOpening << endl;
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
				Animal::DelObjs(tokens, array);
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