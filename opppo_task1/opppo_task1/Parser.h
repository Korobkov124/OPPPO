#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

class Parser {
public:

	static void ParseTxt();

	static int parseDate(const std::string& date);

	static std::vector<std::string> splitString(const std::string& str, char delimiter);
};