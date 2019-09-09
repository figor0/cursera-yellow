#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

#include "test_framework.h"

using namespace std;

set<int>::const_iterator FindNearestElement(
		const set<int>& numbers,
		int border)
{
	if (numbers.empty())
		return numbers.end();
	auto [lower, upper] = numbers.equal_range(border);
	if ( lower == numbers.end())
		return upper;
	if ( upper 	== numbers.end())
		return lower;
	int duration = border - *lower;
	return duration <= *upper - border ? lower : upper;
}

void TestFinder(){
	{
		// extremal cases
		set<int> s{1, 10, 15, 17, 20};
		int result = *FindNearestElement(s, 100);
		Assert( result == 20, "lower case exist: wrong answer "
						+ to_string(result) + " right answer  = 20" );
		result = *FindNearestElement(s, -200);
		Assert( result == 1, "upper case exist: wrong answer "
						+ to_string(result) + " right answer  = 1" );
	}
	{
		set<int> s{1, 10, 15, 17, 20};
		int result = *FindNearestElement(s, 10);
		Assert( result == 10, "border exist: wrong answer "
						+ to_string(result) + " right answer  = 10" );
		result = *FindNearestElement(s, 20);
		Assert( result == 20, "border exist case: wrong answer "
						+ to_string(result) + " right answer  = 20" );
		result = *FindNearestElement(s, 16);
		Assert( result == 15, "both are near case: wrong answer "
						+ to_string(result) + " right answer  = 15" );
	}
	{
		set<int> s{1, 10, 15, 17, 20};
		int result = *FindNearestElement(s, 10);
		Assert( result == 10, "border exist: wrong answer "
						+ to_string(result) + " right answer  = 10" );
		result = *FindNearestElement(s, 20);
		Assert( result == 20, "border exist case: wrong answer "
						+ to_string(result) + " right answer  = 20" );
	}
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(TestFinder, "Test FindNearest");
}

int main() {
//	if (system("./test_cursera")){
//		return 1;
//	}
	TestAll();
//	set<int> s{1 , 10, 15};
	return 0;
}
