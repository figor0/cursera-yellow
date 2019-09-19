#ifndef NODE_H
#define NODE_H
#include "date.h"
#include <memory>

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
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode: public Node
{
public:
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode: public Node
{
public:
	DateComparisonNode(const Comparison& cmp,
					   const Date& date		);

	bool Evaluate(const Date& date, const std::string& event) const override;
	void SetDate(const Date& date);
	void SetComparison(const Comparison& cmp);
private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode: public Node
{
public:
	EventComparisonNode(const Comparison& cmp,
						const std::string& event);

	bool Evaluate(const Date& date, const std::string& event) const override;
	void SetEvent(const std::string& event	);
	void SetComparison(const Comparison& cmp);
private:
	std::string _event;
	Comparison 	_cmp;
};

class LogicalOperationNode: public Node
{
public:
	using pNode = std::shared_ptr<Node>;
	LogicalOperationNode(const LogicalOperation& op, pNode left, pNode right);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	pNode _left;
	pNode _right;
	LogicalOperation _op;
};


#endif // NODE_H
