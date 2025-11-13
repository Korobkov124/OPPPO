#pragma once
#include "Animal.h"

class Bird : public Animal {
public:
	float fast = 0;

	void PrintObj() override;

	bool MatchObj(std::vector<std::string> command) override;

	static void AddToArray(std::vector<std::string>& tokens, std::vector<Animal*>& array);
};