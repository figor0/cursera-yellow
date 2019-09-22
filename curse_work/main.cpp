#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "token.h"
#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
	string first;
	is >> first;
	string second;
	getline(is, second, '\n');
	return first+second;
}

void TestAll();

int main() {
	TestAll();

	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		} else if (command == "Print") {
			db.Print(cout);
		} else if (command == "Del") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		} else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		} else if (command == "Last") {
			try {
					cout << db.Last(ParseDate(is)) << endl;
			} catch (invalid_argument&) {
					cout << "No entries" << endl;
			}
		} else if (command.empty()) {
			continue;
		} else {
			throw logic_error("Unknown command: " + command);
		}
	}
	return 0;
}

void TestParseEvent() {
	{
		istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		istringstream is("  first event  \n  second event");
		vector<string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
	}
}
void TestDate()
{
	int step = 0;
	{
		step++;
		istringstream buffer("2018-11-01");
		Date date = ParseDate(buffer);
		Assert(date == Date(2018, 11, 01), "step " + to_string(step) +
					 " wrong answer: " + to_string(date.GetYear()) +"-"
					 + to_string(date.GetMonth()) + "-" + to_string(date.GetDay()));
	}
	{
		step++;
		Date date1(2018, 03, 01);
		Date date2(2018, 06, 10);
		Assert(date1 < date2, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
		Assert(date1 > date2 == false, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
		Assert(date1 <= date2, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
		Assert(date1 >= date2 == false, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
		Assert(date1 != date2 == true, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
		Assert(date1 == date2 == false, "step " + to_string(step) +
					 " wrong answer: date1 !< date2" );
	}
}

void TestTokenize()
{
	istringstream buffer("date < 2018-11-23");
	vector<Token> tokens = Tokenize(buffer);
	Assert(tokens.size() == 3, "tokenize wrong size");
	Assert(tokens.at(0).type == TokenType::COLUMN && tokens.at(0).value == "date",
				 "first value wrong answer");
	Assert(tokens.at(1).type == TokenType::COMPARE_OP && tokens.at(1).value == "<",
				 "second value wrong answer");
	Assert(tokens.at(2).type == TokenType::DATE && tokens.at(2).value == "2018-11-23",
				 "third value wrong answer");
}
void TestParseCondition()
{
	int step = 0;
	{
		step++;
		istringstream reader("date <= 2018-11-01");
		Date lesser(2017, 11, 01);
		Date greater(2019, 11, 2);
		auto node_result = ParseCondition(reader)->Evaluate(lesser, "event");
		Assert( node_result == true, "lesser case " + to_string(step) + " wrong answer: "
						+ to_string(node_result) + " != true");
	}
	{
		step++;
		istringstream reader("date <= 2018-11-01");
		Date greater(2019, 11, 2);
		auto node_result = ParseCondition(reader)->Evaluate(greater, "event");
		Assert( node_result == false, "greater case " + to_string(step) + " wrong answer: "
						+ to_string(node_result) + " != false");
	}
	{
		step++;
		istringstream reader("date <= 2018-11-01");
		Date equal(2018, 11, 1);
		auto node_result = ParseCondition(reader)->Evaluate(equal, "event");
		Assert( node_result == true, "equal case " + to_string(step) + " wrong answer: "
						+ to_string(node_result) + " != false");
	}
	{
		step++;
		istringstream reader("event != \"wtf\"");
		string equal = "wtf";
		auto node_result = ParseCondition(reader)->Evaluate(Date(1,1,1), equal);
		Assert( node_result == false, "event equal case " + to_string(step) + " wrong answer: "
						+ to_string(node_result) + " != false");
	}
	{
		step++;
		istringstream reader("event != \"wtf\"");
		string no_equal = "no wtf";
		auto node_result = ParseCondition(reader)->Evaluate(Date(1,1,1), no_equal);
		Assert( node_result == true, "event not equal case " + to_string(step) + " wrong answer: "
						+ to_string(node_result) + " != false");
	}
	{
		step++;
		istringstream reader("date < 2000-11-15 AND event == \"wtf\"");
		string equal = "wtf";
		Date date(1995, 2, 9);
		auto node_result = ParseCondition(reader);
		Assert( node_result->Evaluate(date, equal) == true, "hybrid true case " + to_string(step) + " wrong answer: "
						 + " false != true");
		string no_equal = "no wtf";
		Assert( node_result->Evaluate(date, no_equal) == false,
						"hybrid event false case " + to_string(step) + " wrong answer: "
						 + " true != false");
		Date date2(2001, 1, 1);
		Assert( node_result->Evaluate(date2, equal) == false,
						"hybrid date false case " + to_string(step) + " wrong answer: "
						 + " true != false");
	}
}

void TestNodes()
{
	{
		EmptyNode node;
		bool answer = node.Evaluate(Date(2018,1,1), "wtf");
		Assert(answer == true, "Wrong empty node");
	}
	{
		Date date(2017, 5, 29);
		DateComparisonNode node(Comparison::Less, date);
		bool answer = node.Evaluate(Date(2014, 5, 5), "event");
		Assert(answer == true, "DateComparisonNode less case wrong");
		answer = node.Evaluate(Date(2019, 5, 5), "event");
		Assert(answer == false, "DateComparisonNode great case wrong");
	}
	{
		Date lesser(2000, 5, 29);
		Date greater(2020, 5, 29);
		std::shared_ptr<DateComparisonNode> less(new DateComparisonNode(Comparison::Greater, lesser));
		std::shared_ptr<DateComparisonNode> greate(new DateComparisonNode(Comparison::Less, greater));
		LogicalOperationNode op(LogicalOperation::And, greate, less);
		bool answer = op.Evaluate(Date(2005, 5, 29), "event");
		Assert(answer == true, "LogicalOperation: wrong answer");
		answer = op.Evaluate(Date(2021, 5, 29), "event");
		Assert(answer == false, "LogicalOperation: wrong answer");
	}
}

void TestDateOutput()
{
	ostringstream reader;
	Date date(1, 1, 1);
	reader << date;
	Assert(reader.str() == "0001-01-01", "1-1-1 wrong answer: "
				 + reader.str() );
}

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestDate, "TestParseDate");
	tr.RunTest(TestTokenize, "TestTokenize");
	tr.RunTest(TestNodes, "TestNodes");
	tr.RunTest(TestDateOutput, "TestDateOutput");
	tr.RunTest(TestParseCondition, "TestParseCondition");
}
