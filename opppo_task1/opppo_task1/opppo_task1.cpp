#include <clocale>
#include "Parser.h"

int main() {
	setlocale(LC_ALL, "ru");
	
	std::cout << "Парсинг текстовых команд из файла с расширением .txt" << std::endl;
	Parser::ParseTxt();

	return 0;
}