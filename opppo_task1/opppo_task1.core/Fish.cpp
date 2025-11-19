#include "Fish.h"

#include "pch.h"

bool Fish::MatchObj(std::vector<std::string> command)
{
    if (command[0] == "livingPlace")
    {
        int value = stoi(command[2]);
        if (command[1] == "==")
            return livingPlace == value;
        if (command[1] == "!=")
            return livingPlace != value;
    }

    return Animal::MatchObj(command);
}

void Fish::PrintObj()
{
    std::string placeStr;
    switch (livingPlace)
    {
    case river:
        placeStr = "River";
        break;
    case lake:
        placeStr = "Lake";
        break;
    case sea:
        placeStr = "Sea";
        break;
    default:
        placeStr = "Unknow";
        break;
    }
    std::cout << "Name: " << name << " Living Place: " << placeStr << std::endl;
}

void Fish::AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array)
{
    auto currentFish = std::make_unique<Fish>();
    currentFish->name = tokens[0];

    if (stoi(tokens[1]) >= Fish::river && stoi(tokens[1]) <= Fish::sea)
    {
        currentFish->livingPlace = static_cast<Fish::placeEnum>(stoi(tokens[1]));
        array.push_back(std::move(currentFish));
        return;
    }
    else
    {
        throw std::invalid_argument("Incerrect value of leaving place " + tokens[0] + "!\n");
        return;
    }
}