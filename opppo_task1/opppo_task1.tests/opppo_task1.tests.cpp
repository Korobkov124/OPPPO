#include <string>
#include <vector>
#include <typeinfo>
#include "pch.h"
#include "CppUnitTest.h"
#include "../opppo_task1/Parser.h"
#include "../opppo_task1/Animal.h"
#include "../opppo_task1/Fish.h"
#include "../opppo_task1/Bird.h"
#include "../opppo_task1/Insect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace opppoTests {
	TEST_CLASS(ParserTests) {
	public:
		TEST_METHOD(TestParseDate)
		{
			auto funcParseDate = [](const std::string& testLine) {
				return Parser::parseDate(testLine);
				};

			Assert::IsTrue(19000310 == funcParseDate("10.03.1900"));
			Assert::IsTrue(19010310 == funcParseDate("10.03.1901"));
			Assert::IsTrue(19001110 == funcParseDate("10.11.1900"));
			Assert::IsTrue(19000311 == funcParseDate("11.03.1900"));
		}
		TEST_METHOD(TestParseInvalidDate) {
			auto funcInvalidDate = [](const std::string& testLine) {
				return [testLine]() {return Parser::parseDate(testLine); };
				};

			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("32.10.2010"));
			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("13.13.2013"));
			Assert::ExpectException<std::invalid_argument>(funcInvalidDate("ae.ae.ae"));
		}
		TEST_METHOD(TestSplitString) {
			auto funcSplitString = [](const std::string& testLine, const char& delimiter) {
				return Parser::splitString(testLine, delimiter);
				};

			std::vector<std::string> testVector{ "ADD", "Karp", "1" };

			Assert::IsTrue(testVector == funcSplitString("ADD Karp 1", ' '));
			Assert::IsTrue(testVector == funcSplitString("ADD.Karp.1", '.'));
			Assert::IsTrue(testVector == funcSplitString("ADD  Karp 1", ' '));
		}
	};

	TEST_CLASS(AnimalTests) {
	public:
		TEST_METHOD(TestAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Animal::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Fish Karp 1", ' '), testArray);
			funcAddToArray(funcAddVect("Bird Scopa 10.2", ' '), testArray);
			funcAddToArray(funcAddVect("Insect Scopa 10 10.10.2000", ' '), testArray);

			Assert::IsTrue(typeid(*testArray[0]) == typeid(Fish));
			Assert::IsTrue(typeid(*testArray[1]) == typeid(Bird));
			Assert::IsTrue(typeid(*testArray[2]) == typeid(Insect));
		}
		TEST_METHOD(TestInvalidAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return [&testTokens, &testArray]() { Animal::AddToArray(testTokens, testArray); };
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Fishh Karp 1", ' '), testArray));
			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Fish1 Karp 1", ' '), testArray));
			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Ôèø Karp 1", ' '), testArray));
		}
		TEST_METHOD(TestDelObj) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Animal::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			auto funcDelFromArray = [](std::vector<std::string> testCommand, std::vector<Animal*>& testArray) {
				return Animal::DelObj(testCommand, testArray);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Fish Karp 1", ' '), testArray);
			funcAddToArray(funcAddVect("Bird Scopa 10.2", ' '), testArray);
			funcAddToArray(funcAddVect("Insect Scopa 10 10.10.2000", ' '), testArray);

			Assert::IsTrue(3 == testArray.size());

			funcDelFromArray(funcAddVect("name == Karp", ' '), testArray);

			Assert::IsTrue(2 == testArray.size());

			funcDelFromArray(funcAddVect("name != Karp", ' '), testArray);

			Assert::IsTrue(testArray.empty());
		}
		TEST_METHOD(TestMatchObj) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Animal::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Fish Karp 1", ' '), testArray);
			funcAddToArray(funcAddVect("Bird Scopa 10.2", ' '), testArray);
			funcAddToArray(funcAddVect("Insect Scopa 10 10.10.2000", ' '), testArray);

			Assert::IsTrue(testArray[0]->MatchObj(funcAddVect("name == Karp", ' ')));
			Assert::IsTrue(testArray[1]->MatchObj(funcAddVect("name == Scopa", ' ')));
			Assert::IsTrue(testArray[2]->MatchObj(funcAddVect("name == Scopa", ' ')));
			Assert::IsFalse(testArray[0]->MatchObj(funcAddVect("name != Karp", ' ')));
			Assert::IsFalse(testArray[1]->MatchObj(funcAddVect("name != Scopa", ' ')));
			Assert::IsFalse(testArray[2]->MatchObj(funcAddVect("name != Scopa", ' ')));
		}
	};

	TEST_CLASS(FishTests) {
	public:
		TEST_METHOD(TestAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Fish::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Karp 1", ' '), testArray);
			funcAddToArray(funcAddVect("Lesch 2", ' '), testArray);
			funcAddToArray(funcAddVect("Som 3", ' '), testArray);

			Assert::IsTrue(typeid(*testArray[0]) == typeid(Fish));
			Assert::IsTrue(typeid(*testArray[1]) == typeid(Fish));
			Assert::IsTrue(typeid(*testArray[2]) == typeid(Fish));
		}
		TEST_METHOD(TestInvalidAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return [&testTokens, &testArray]() {return Fish::AddToArray(testTokens, testArray); };
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Karp 4", ' '), testArray));
		}
		TEST_METHOD(TestMatchObj) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Fish::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Karp 1", ' '), testArray);
			funcAddToArray(funcAddVect("Lesch 2", ' '), testArray);
			funcAddToArray(funcAddVect("Som 3", ' '), testArray);

			Assert::IsTrue(testArray[0]->MatchObj(funcAddVect("livingPlace == 1", ' ')));
			Assert::IsTrue(testArray[1]->MatchObj(funcAddVect("livingPlace == 2", ' ')));
			Assert::IsTrue(testArray[2]->MatchObj(funcAddVect("livingPlace == 3", ' ')));
			Assert::IsFalse(testArray[0]->MatchObj(funcAddVect("livingPlace != 1", ' ')));
			Assert::IsFalse(testArray[1]->MatchObj(funcAddVect("livingPlace != 2", ' ')));
			Assert::IsFalse(testArray[2]->MatchObj(funcAddVect("livingPlace != 3", ' ')));
		}
	};


	TEST_CLASS(BirdTests) {
	public:
		TEST_METHOD(TestAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Bird::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Eagle 1", ' '), testArray);
			funcAddToArray(funcAddVect("Pigeon 2", ' '), testArray);
			funcAddToArray(funcAddVect("Aist 3", ' '), testArray);

			Assert::IsTrue(typeid(*testArray[0]) == typeid(Bird));
			Assert::IsTrue(typeid(*testArray[1]) == typeid(Bird));
			Assert::IsTrue(typeid(*testArray[2]) == typeid(Bird));
		}
		TEST_METHOD(TestInvalidAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return [&testTokens, &testArray]() {return Bird::AddToArray(testTokens, testArray); };
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Bird asd", ' '), testArray));
		}
		TEST_METHOD(TestMatchObj) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Bird::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Eagle 10.2", ' '), testArray);
			funcAddToArray(funcAddVect("Pigeon 15.3", ' '), testArray);
			funcAddToArray(funcAddVect("Aist 25.4", ' '), testArray);

			Assert::IsTrue(testArray[0]->MatchObj(funcAddVect("fast == 10.2", ' ')));
			Assert::IsTrue(testArray[1]->MatchObj(funcAddVect("fast == 15.3", ' ')));
			Assert::IsTrue(testArray[2]->MatchObj(funcAddVect("fast == 25.4", ' ')));
			Assert::IsFalse(testArray[0]->MatchObj(funcAddVect("fast <= 1", ' ')));
			Assert::IsFalse(testArray[1]->MatchObj(funcAddVect("fast < 2", ' ')));
			Assert::IsFalse(testArray[2]->MatchObj(funcAddVect("fast > 30", ' ')));
		}
	};

	TEST_CLASS(InsectTests) {
	public:
		TEST_METHOD(TestAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Insect::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Bug 10 10.10.2020", ' '), testArray);
			funcAddToArray(funcAddVect("Cockroach 7 15.01.1900", ' '), testArray);
			funcAddToArray(funcAddVect("Spider 20 09.03.1800", ' '), testArray);

			Assert::IsTrue(typeid(*testArray[0]) == typeid(Insect));
			Assert::IsTrue(typeid(*testArray[1]) == typeid(Insect));
			Assert::IsTrue(typeid(*testArray[2]) == typeid(Insect));
		}
		TEST_METHOD(TestInvalidAddToArray) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return [&testTokens, &testArray]() {return Insect::AddToArray(testTokens, testArray); };
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			Assert::ExpectException<std::invalid_argument>(funcAddToArray(funcAddVect("Bug asd 10.10.2020", ' '), testArray));
		}
		TEST_METHOD(TestMatchObj) {
			auto funcAddToArray = [](std::vector<std::string>& testTokens, std::vector<Animal*>& testArray) {
				return Insect::AddToArray(testTokens, testArray);
				};

			auto funcAddVect = [](const std::string& testTokensString, const char& delimiter) {
				return Parser::splitString(testTokensString, delimiter);
				};

			std::vector<Animal*> testArray;

			funcAddToArray(funcAddVect("Bug 10 10.10.2020", ' '), testArray);
			funcAddToArray(funcAddVect("Cockroach 7 15.01.1900", ' '), testArray);
			funcAddToArray(funcAddVect("Spider 20 09.03.1800", ' '), testArray);

			Assert::IsTrue(testArray[0]->MatchObj(funcAddVect("size == 10", ' ')));
			Assert::IsTrue(testArray[1]->MatchObj(funcAddVect("size == 7", ' ')));
			Assert::IsTrue(testArray[2]->MatchObj(funcAddVect("size == 20", ' ')));
			Assert::IsFalse(testArray[0]->MatchObj(funcAddVect("size <= 5", ' ')));
			Assert::IsFalse(testArray[1]->MatchObj(funcAddVect("size < 2", ' ')));
			Assert::IsFalse(testArray[2]->MatchObj(funcAddVect("size > 30", ' ')));

			Assert::IsTrue(testArray[0]->MatchObj(funcAddVect("dateOfOpening == 10.10.2020", ' ')));
			Assert::IsTrue(testArray[1]->MatchObj(funcAddVect("dateOfOpening == 15.01.1900", ' ')));
			Assert::IsTrue(testArray[2]->MatchObj(funcAddVect("dateOfOpening == 09.03.1800", ' ')));
			Assert::IsFalse(testArray[0]->MatchObj(funcAddVect("dateOfOpening != 10.10.2020", ' ')));
			Assert::IsFalse(testArray[1]->MatchObj(funcAddVect("dateOfOpening > 15.01.1920", ' ')));
			Assert::IsFalse(testArray[2]->MatchObj(funcAddVect("dateOfOpening < 09.03.1720", ' ')));
		}
	};
}