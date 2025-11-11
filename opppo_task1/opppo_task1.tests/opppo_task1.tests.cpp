#include <string>
#include <vector>
#include "pch.h"
#include "CppUnitTest.h"
#include "../opppo_task1/Parser.h"
#include "../opppo_task1/Animal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTests
{
	TEST_CLASS(ParserTests)
	{
	public:
		TEST_METHOD(TestParseDate)
		{
			auto funcParseDate = [](const std::string& testLine) {
				return [testLine]() { return Parser::parseDate(testLine); };
				};

			Assert::IsTrue(19000310 == funcParseDate("10.03.1900")());
			Assert::IsTrue(19010310 == funcParseDate("10.03.1901")());
			Assert::IsTrue(19001110 == funcParseDate("10.11.1900")());
			Assert::IsTrue(19000311 == funcParseDate("11.03.1900")());
		}
		TEST_METHOD(TestParseInvalidDate) {
			auto funcInvalidDate = [](const std::string& testLine) {
				return [testLine]() { return Parser::parseDate(testLine); };
			};

			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("32.10.2010"));
			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("13.13.2013"));
			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("ae.ae.ae"));
		}
		TEST_METHOD(TestSplitString) {
			auto funcSplitString = [](const std::string& testLine, const char& delimiter) {
				return [testLine, delimiter]() { return Parser::splitString(testLine, delimiter); };
				};

			std::vector<std::string> testVector{ "ADD", "Karp", "1" };
			Assert::IsTrue(testVector == funcSplitString("ADD Karp 1", ' ')());
			Assert::IsTrue(testVector == funcSplitString("ADD.Karp.1", '.')());
			Assert::IsTrue(testVector == funcSplitString("ADD  Karp 1", ' ')());
		}
		TEST_METHOD(TestParseTxt) {
			
		}
	};
}
