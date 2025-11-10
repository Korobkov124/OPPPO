#include "Parser.h"
#include "Animal.h"

int Parser::parseDate(const std::string& date) {
	int day = std::stoi(date.substr(0, 2));
	int month = std::stoi(date.substr(3, 2));
	int year = std::stoi(date.substr(6, 4));
	return year * 10000 + month * 100 + day;
}

void Parser::ParseTxt() {
	std::string currentLine;
	std::ifstream iftxt("parsed.txt");
	int lineCount = 0;
	std::vector<Animal*> array;

	if (iftxt.is_open()) {

		while (getline(iftxt, currentLine)) {
			lineCount++;
			std::cout << "Команда " << lineCount << ": " << currentLine << std::endl;
			std::vector<std::string> tokens = Parser::splitString(currentLine, ' ');

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

std::vector<std::string> Parser::splitString(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);

	while (getline(tokenStream, token, delimiter)) {

		if (!token.empty()) {
			tokens.push_back(token);
		}
	}

	return tokens;
}