#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "test_framework.h"
#include "numeric_expression.h"

using namespace std;

void NodeFiller_test()
{
	int step = 0;
	{
		step++;
		stringstream writer("* 3");
		Node result;
		writer >> result;
		bool right = result.value == 3 && result.operand == '*';
		Assert(right, "case " + to_string(step) + " wrong: "
					 + "\n right result: value = * " + to_string(3));
	}
	{
		step++;
		stringstream writer("/ 200");
		Node result;
		writer >> result;
		bool right = result.value == 200 && result.operand == '/';
		Assert(right, "case " + to_string(step) + " wrong: "
					 + "\n right result: value = * " + to_string(3));
	}
	{
		step++;
		stringstream writer("+ 30");
		Node result;
		writer >> result;
		bool right = result.value == 30 && result.operand == '+';
		Assert(right, "case " + to_string(step) + " wrong: "
					 + "\n right result: value = * " + to_string(3));
	}
}

void NodeReader_test()
{
	int step = 0;
	{
		stringstream reader;
		reader << Node{'+', 20};
		bool right = reader.str() == "+ 20";
		Assert(right, "case: " + to_string(step) +
					 "answer: " + reader.str() +
					 "right answer: + 20");
	}
}

void expressionOutputTest()
{
	int step = 0;
	{
		step++;
		string input = "* 3";
		int first = 9;
		stringstream stream;
		stream << Expression(input, 1, first);
		bool right = stream.str() == "(9) * 3";
		Assert(right, "case wrong : answer = " + stream.str() + '\n');
	}
	{
		step++;
		string input = "* 3 * 4 + 5";
		int first = 9;
		stringstream stream;
		stream << Expression(input, 3, first);
		bool right = stream.str() == "(((9) * 3) * 4) + 5";
		Assert(right, "case wrong : answer = " + stream.str() + '\n');
	}
	{
		step++;
		string input;
		int first = 9;
		stringstream stream;
		stream << Expression(input, 0, first);
		bool right = stream.str() == "9";
		Assert(right, "case " + to_string(step) + " wrong answer = " + stream.str() + '\n');
	}
}

void ScopeNeedTest()
{
	int step = 0;
	{
		step++;
		string input("* 3 + 4 / 5");
		vector<Node> buffer = vector_filer(input, 3);
		int result = scopeNeed(buffer);
		Assert( result == 1, "Step " + to_string(step) + ": "
					 + " wrong answer: " + to_string(result) +
						"right answer: 1");
	}
	{
		step++;
		string input;
		vector<Node> buffer = vector_filer(input, 0);
		int result = scopeNeed(buffer);
		Assert( result == 0, "Step " + to_string(step) + ": "
					 + " wrong answer: " + to_string(result) +
						"right answer: 0");
	}
	{
		step++;
		string input("* 3 + 4 - 5");
		vector<Node> buffer = vector_filer(input, 3);
		int result = scopeNeed(buffer);
		Assert( result == 0, "Step " + to_string(step) + ": "
					 + " wrong answer: " + to_string(result) +
						"right answer: 0");
	}
	{
		step++;
		string input("+ 3 * 4 + 5 / 3");
		vector<Node> buffer = vector_filer(input, 4);
		int result = scopeNeed(buffer);
		Assert( result == 2, "Step " + to_string(step) + ": "
					 + " wrong answer: " + to_string(result) +
						"right answer: 2");
	}
}
void TestAll(){
	TestRunner tr;
	tr.RunTest(NodeFiller_test, "iostream >> Node test");
	tr.RunTest(NodeReader_test, "ostream << Node test");
	tr.RunTest(expressionOutputTest, "ostream << expression test");
	tr.RunTest(ScopeNeedTest, "Scope need test");
}
int main()
{
	TestAll();
	return 0;
}
