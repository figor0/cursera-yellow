#include "test_framework.h"
#include "phone_number.h"

void TestSpliter()
{
	{
		string number("");
		vector<string> result = split( number.begin(), number.end(), '-');
		Assert(result.empty(), "Empty case: wrong");
	}
	{
		string number("+7-495-1112233");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 3, "Common case: wrong size: "
			   + to_string(result.size()) + ". Right size = 3");
		Assert(result.at(0) == "+7", "Common case: wrong Country code: "
			   + result.at(0) + " Right: +7");
		Assert( result.at(1) == "495", "Common case: wrong city code: "
				+ result.at(1) + " Right: 495");
		Assert( result.at(2) == "1112233", "Common case: wrong local code: "
				+ result.at(2) + " Right: 495");

	}
	{
		string number("+dlf9-abc-cdefgtr");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 3, "Literal case: wrong size: "
			   + to_string(result.size()) + ". Right size = 3");
		Assert(result.at(0) == "+dlf9", "Literal case: wrong Country code: "
			   + result.at(0) + "right: +dlf9");
		Assert( result.at(1) == "abc", "Literal case: wrong city code: "
				+ result.at(1) + "right: abc");
		Assert( result.at(2) == "cdefgtr", "Literal case: wrong local code: "
				+ result.at(2) + "right: cdefgtr");

	}
	{
		string number("+7-495-111-22-33");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 5, "International case: wrong size: "
			   + to_string(result.size()) + ". Right size = 3");
		Assert(result.at(0) == "+7", "International case: wrong Country code: "
			   + result.at(0) + "right: +7");
		Assert( result.at(1) == "495", "International case: wrong city code: "
				+ result.at(1) + "right: 495");
		Assert( result.at(2) == "111", "International case: wrong first part of local code: "
				+ result.at(2) + "right: 111");
		Assert( result.at(3) == "22", "International case: wrong second part of local code: "
				+ result.at(3) + "right: 22");
		Assert( result.at(4) == "33", "International case: wrong third part local code: "
				+ result.at(4) + "right: 33");
	}
	{
		string number("---");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 3, "--- case: wrong size = " + to_string(result.size())
				 + " Rihgt size = 3");
	}
	{
		string number("asdfasdf");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 1, "just word case: wrong size");
		Assert(result.at(0) == number, "just word case: wrong answer: " +
				 result.at(0) + " Right: " + number);
	}
	{
		string number("asdfsd-awerwer");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 2, "one - case: wrong size " + to_string(result.size())
			   + ". Right size = 2");
	}
	{
		string number("+--26-asdfg");
		auto result = split(number.begin(), number.end(), '-');
		Assert(result.size() == 4, "cursera talk case: wrong size " + to_string(result.size())
				 + ". Right size = 4");
		Assert(result.at(0) == "+", "cursera talk case: wrong country: "
					 + result.at(0) + " right answer = +");
		Assert( result.at(1).empty(), "cursera talk case: must be empty");
		Assert(result.at(2) == "26", "cursera talk case: wrong country: "
					 + result.at(2) + " right answer = +");
		Assert(result.at(3) == "asdfg", "cursera talk case: wrong country: "
					 + result.at(3) + " right answer = +");
	}
}

void TestPhoneNumberConstructor()
{
	{
		string input("+7-981-8764773");
		PhoneNumber number(input);
		Assert(number.GetCountryCode() == "7"
					 && number.GetCityCode() == "981"
					 && number.GetLocalNumber() == "8764773",
					 "my number: wrong answer : +"
					 + number.GetCountryCode() + number.GetCityCode()
					 + number.GetLocalNumber() + " right = +7-981-8764773");
	}
	{
		string input("+7-981-876-47-73");
		PhoneNumber number(input);
		Assert(number.GetCountryCode() == "7"
					 && number.GetCityCode() == "981"
					 && number.GetLocalNumber() == "8764773",
					 "my number international: wrong answer : +"
					 + number.GetCountryCode() + number.GetCityCode()
					 + number.GetLocalNumber() + " right = +7-981-8764773");
	}
}

void ConstructorExceptionTest()
{
	{
		string input("");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}
	{
		string input("+--");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}
	{
		string input("723452342");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}

	{
		string input("+723452342");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}
	{
		string input("+7-23452342");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}
	{
		string input("---");
		try {
			PhoneNumber number(input);
			throw invalid_argument("must throw exception before");
		} catch (invalid_argument& ec) {
			string erWhat = ec.what();
			Assert( erWhat.empty(), "Ecxeption case wrong answer: " + erWhat);
		}
	}
}


void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestSpliter, "Split test");
	tr.RunTest(TestPhoneNumberConstructor, "Test constructor");
	tr.RunTest(ConstructorExceptionTest, "Exception test");
}

int main()
{
	TestAll();
	return 0;
}
