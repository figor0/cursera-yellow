#ifndef NODE_H
#define NODE_H
#include "date.h"

enum class Comparison{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation
{
	Or,
	And
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode: public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event);
};

class DateComparisonNode: public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event);
};

class EventComparisonNode: public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event);
};

class LogicalOperationNode: public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event);
};


#endif // NODE_H
