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
			Assert::AreEqual(19000310, Parser::parseDate("10.03.1900"));
			Assert::AreEqual(19010310, Parser::parseDate("10.03.1901"));
			Assert::AreEqual(19001110, Parser::parseDate("10.11.1900"));
			Assert::AreEqual(19000311, Parser::parseDate("11.03.1900"));
		}

		TEST_METHOD(TestParseInvalidDate) {
			auto func = [] { Parser::parseDate("13.13.2013"); };
			Assert::ExpectException<std::invalid_argument>(func);
		}
	};
}
