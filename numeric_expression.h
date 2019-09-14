#ifndef NUMERIC_EXPRESSION_H
#define NUMERIC_EXPRESSION_H

#include <queue>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node;

enum class Operation{
	UNK = 0,
	SUM = 1,
	MIN = 1,
	MUL = 2,
	DIV = 2
};

Operation int2oper(char operand){
	switch (operand){
	case '+':{
		return Operation::SUM;
	}
	case '-':{
		return Operation::MIN;
	}
	case '*':{
		return Operation::MUL;
	}
	case '/':{
		return Operation::DIV;
	}
	default: return Operation::UNK;
	}
}

istream& operator>>(istream& writer, Operation& oper){
	char operand;
	writer >> operand;
	oper = int2oper(operand);
	return writer;
}

struct Node{
	Operation type;
	int value;
};

bool operator<(const Operation& lhs, const Operation& rhs)
{
	return static_cast<int>(lhs) < static_cast<int>(rhs);
}

bool operator<(const Node& lhs, const Node& rhs)
{
	return lhs < rhs;
}

istream& operator>>(istream& writer, Node& node){
	writer >> node.type >> node.value;
	return writer;
}

class Expression
{
public:
	Expression(queue<Node> nodes)
	{
		stringstream stream(expression);

	}
private:
	string expression;
};

ostream& operator<<(ostream& reader, Expression& expr){
	reader << expr;
	return reader;
}




















#endif // NUMERIC_EXPRESSION_H
