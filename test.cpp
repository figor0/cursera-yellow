#include "test_framework.h"
#include "phone_number.h"

void TestSpliter()
{
	{
		string number("");
		vector<string> result = split(number);
		Assert(result.empty(), "Empty case: wrong");
	}
	{
		string number("+7-495-1112233");
		auto result = split(number);
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
		auto result = split(number);
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
		auto result = split(number);
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
		string wrong("---");
		auto result = split(wrong);
		Assert(result.size() == 0, "--- case: wrong size =" + to_string(result.size())
			   + " Rihgt size = 0");
	}
	{
		string wrong("asdfasdf");
		auto result = split(wrong);
		Assert(result.size() == 1, "just word case: wrong size");
		Assert(result.at(0) == wrong, "just word case: wrong answer: " +
			   result.at(0) + ". Right: " + wrong);
	}
	{
		string wrong("asdfsd-awerwer");
		auto result = split(wrong);
		Assert(result.size() == 2, "one - case: wrong size " + to_string(result.size())
			   + ". Right size = 2");
	}
}


void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestSpliter, "Split test");
}

int main()
{
	TestAll();
	return 0;
}
