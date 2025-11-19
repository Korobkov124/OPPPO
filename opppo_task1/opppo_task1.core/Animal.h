#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"

class Animal
{
public:
    std::string name;

    static void AddToArray(std::vector<std::string>& tokens, std::vector<std::unique_ptr<Animal>>& array);

    static void DelObj(std::vector<std::string> tokens, std::vector<std::unique_ptr<Animal>>& array);

    virtual bool MatchObj(std::vector<std::string> command);

    virtual void PrintObj();

    static void PrintArray(const std::vector<std::unique_ptr<Animal>>& array);

    virtual ~Animal() = default;
};
#endif // ANIMAL_H