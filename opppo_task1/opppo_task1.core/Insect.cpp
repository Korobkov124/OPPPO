#include "Insect.h"

#include "pch.h"

bool Insect::MatchObj(std::vector<std::string> command)
{
    if (command[0] == "size")
    {
        int value = stoi(command[2]);
        if (command[1] == "==")
            return size == value;
        if (command[1] == "!=")
            return size != value;
        if (command[1] == ">")
            return size > value;
        if (command[1] == "<")
            return size < value;
        if (command[1] == ">=")
            return size >= value;
        if (command[1] == "<=")
            return size <= value;
    }
    else if (command[0] == "dateOfOpening")
    {
        int valueDate = Parser::parseDate(command[2]);
        int valueOwnDate = Parser::parseDate(dateOfOpening);
        if (command[1] == "==")
            return valueOwnDate == valueDate;
        if (command[1] == "!=")
            return valueOwnDate != valueDate;
        if (command[1] == ">")
            return valueOwnDate > valueDate;
        if (command[1] == "<")
            return valueOwnDate < valueDate;
        if (command[1] == ">=")
            return valueOwnDate >= valueDate;
        if (command[1] == "<=")
            return valueOwnDate <= valueDate;
    }

    return Animal::MatchObj(command);
}

void Insect::PrintObj()
{
    std::cout << "Name: " << name << " Size: " << size << "sm^2" << " Date of opening: " << dateOfOpening << std::endl;
}

void Insect::AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array)
{
    auto currentInsect = std::make_unique<Insect>();
    currentInsect->name = tokens[0];

    if (stoi(tokens[1]) >= 0)
    {
        currentInsect->size = stof(tokens[1]);
        currentInsect->dateOfOpening = tokens[2];
        array.push_back(std::move(currentInsect));
        return;
    }
    else
    {
        throw std::invalid_argument("Incorrect value of size " + tokens[0] + "!\n");
        return;
    }
}