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
		Assert(result.size() == 3 && result == {})
	}
}


void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestSpliter, "Split test");
}

int main(){

	return 0;
}
