#include "pch.h"
#include "Parser.h"
#include "Animal.h"

int Parser::parseDate(const std::string& date)
{
    if (date.size() != 10 || date[2] != '.' || date[5] != '.')
    {
        throw std::invalid_argument("Incorrect format of date!");
    }

    int day, month, year;
    try
    {
        day = std::stoi(date.substr(0, 2));
        month = std::stoi(date.substr(3, 2));
        year = std::stoi(date.substr(6, 4));
    }
    catch (const std::invalid_argument&)
    {
        throw std::invalid_argument("Incorrect value of date!");
    }
    catch (const std::out_of_range&)
    {
        throw std::out_of_range("Too large value of date!");
    }

    if (!Parser::ValidateDate(day, month))
    {
        throw std::invalid_argument("Incorrect value of day|month!");
    }

    return year * 10000 + month * 100 + day;
}

void Parser::ParseTxt(std::string filePath)
{
    std::string currentLine;
    std::ifstream iftxt(filePath);
    int lineCount = 0;
    std::vector<std::unique_ptr<Animal>> array;

    if (iftxt.is_open())
    {
        while (getline(iftxt, currentLine))
        {
            lineCount++;
            std::cout << "Command " << lineCount << ": " << currentLine << std::endl;
            std::vector<std::string> tokens = Parser::splitString(currentLine, ' ');

            if (tokens.empty())
                continue;

            if (tokens[0] == "ADD")
            {
                tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
                Animal::AddToArray(tokens, array);
            }

            if (tokens[0] == "REM")
            {
                tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
                Animal::DelObj(tokens, array);
            }

            if (tokens[0] == "PRINT")
            {
                tokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
                Animal::PrintArray(array);
            }
        }
    }
};

std::vector<std::string> Parser::splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (getline(tokenStream, token, delimiter))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}

bool Parser::ValidateDate(int day, int month)
{
    if (day > 31 || day <= 0)
    {
        return false;
    }
    if (month > 12 || month <= 0)
    {
        return false;
    }
    return true;
}