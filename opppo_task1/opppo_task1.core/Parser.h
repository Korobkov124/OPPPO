#pragma once
#include "pch.h"

class Parser {
public:
	static void ParseTxt(std::string filePath);

	static int parseDate(const std::string& date);

	static std::vector<std::string> splitString(const std::string& str, char delimiter);

private:
	static bool ValidateDate(int date, int month);
};