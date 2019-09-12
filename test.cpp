#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "test_framework.h"
#include "FindStartWith.h"
using namespace std;


void TestFindStartsWith()
{
	int step = 0;
	{
		step++;
		vector<string> strings{};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'a');
		bool result = 	pairIt.second - pairIt.first 	== 0 &&
						pairIt.first == strings.end() && pairIt.second == strings.end();
		Assert(result, "Empty case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"abc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'a');
		bool result = 	pairIt.second - pairIt.first 	== 1 &&
						*pairIt.first == "abc";
		Assert(result, "Single element exist case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"bbc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'a');
		bool result = 	pairIt.second - pairIt.first 	== 0 &&
						pairIt.first == strings.begin() && pairIt.second == strings.begin();
		Assert(result, "Single element not exist and prefix lower it case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"bbc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'c');
		bool result = 	pairIt.second - pairIt.first 	== 0 &&
						pairIt.first == strings.end() && pairIt.second == strings.end();
		Assert(result, "Single element not exist and prefix upper it case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"abc", "acb", "bca", "cda"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'b');
		bool result = 	pairIt.second - pairIt.first 	== 1 &&
						*pairIt.first == "bca";
		Assert(result, "One element case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"abc", "acdsfadsf", "adr", "hat", "hbt"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'a');
		bool result = 	pairIt.second - pairIt.first 	== 3
						&&	*pairIt.first 				== "abc"
						&&	*prev(pairIt.second)				== "adr";
		Assert(result, "case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first)
						+"\n firstIt value: " + *pairIt.first + " second value: " + *pairIt.second);
	}
	{
		step++;
		vector<string> strings{"abc", "acdsfadsf", "adr", "bat", "bbt", "cydfs", "cyrerw"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), 'b');
		bool result = 	pairIt.second - pairIt.first 	== 2
						&&	*pairIt.first 				== "bat"
						&&	*prev(pairIt.second)				== "bbt";
		Assert(result, "case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first)
						+"\n firstIt value: " + *pairIt.first + " second value: " + *pairIt.second);
	}
}

void TestPrefixFindStartsWith()
{
	int step = 0;
	{
		step++;
		vector<string> strings{};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "a");
		bool result = 	pairIt.second - pairIt.first 	== 0 &&
						pairIt.first == strings.end() && pairIt.second == strings.end();
		Assert(result, "Empty case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"abc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "ab");
		bool result = 	pairIt.second - pairIt.first 	== 1 &&
						*pairIt.first == "abc";
		Assert(result, "Single element exist case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"bbc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "a");
		bool result = 	pairIt.second - pairIt.first 	== 1 &&
						pairIt.first == strings.begin() && pairIt.second == strings.end();
		Assert(result, "Single element not exist and prefix lower it case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"bbc"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "c");
		bool result = 	pairIt.second - pairIt.first 	== 0 &&
						pairIt.first == strings.end() && pairIt.second == strings.end();
		Assert(result, "Single element not exist and prefix upper it case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first));
	}
	{
		step++;
		vector<string> strings{"abc", "acb", "bca", "cda"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "bc");
		bool result = 	pairIt.second - pairIt.first 	== 1 &&
						*pairIt.first == "bca" && *pairIt.second == "cda";
		Assert(result, "One element case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first)
						+"\nfirst: " + *pairIt.first + " second: " + *pairIt.second);
	}
	{
		step++;
		vector<string> strings{"abc", "acdsfadsf", "adr", "hat", "hbt"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "a");
		bool result = 	pairIt.second - pairIt.first 	== 3
						&&	*pairIt.first 				== "abc"
						&&	*prev(pairIt.second)				== "adr";
		Assert(result, "case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first)
						+"\n firstIt value: " + *pairIt.first + " second value: " + *pairIt.second);
	}
	{
		step++;
		vector<string> strings{"abc", "acdsfadsf", "adr", "bat", "bbt", "cydfs", "cyrerw"};
		auto pairIt = FindStartsWith(strings.begin(), strings.end(), "b");
		bool result = 	pairIt.second - pairIt.first 	== 2
						&&	*pairIt.first 				== "bat"
						&&	*prev(pairIt.second)				== "bbt";
		Assert(result, "case " + to_string(step) + " wrong" +
						+"\nresult: it space width = " + to_string(pairIt.second - pairIt.first)
						+"\n firstIt value: " + *pairIt.first + " second value: " + *pairIt.second);
	}
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(TestFindStartsWith, "FindStartsWith literal test");
	tr.RunTest(TestPrefixFindStartsWith, "FindStartsWith string test");
}
int main()
{
	TestAll();
	return 0;
}
