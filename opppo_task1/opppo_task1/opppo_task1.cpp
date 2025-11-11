#include <clocale>
#include "Parser.h"

int main() {
	setlocale(LC_ALL, "ru");
	
	std::cout << "Парсинг текстовых команд из файла с расширением .txt" << std::endl;

    try {
        int dateCode = Parser::parseDate("parsed.txt");
        std::cout << "Дата успешно распарсена: " << dateCode << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

	return 0;
}