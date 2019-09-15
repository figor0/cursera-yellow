#ifndef LOCONIC_NUMERIC_EXPRESSION_H
#define LOCONIC_NUMERIC_EXPRESSION_H

#include <queue>
#include <stack>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Expression;
struct Node;
istream& operator>>(istream& writer, Node& node);
ostream& operator<<(ostream& reader, Expression& expr);
int char2oper(char operand);
istream& operator>>(istream& writer, stack<Node> nodes);


int char2oper(char operand){
	switch (operand){
	case '+':{
		return 0;
	}
	case '-':{
		return 0;
	}
	case '*':{
		return 1;
	}
	case '/':{
		return 1;
	}
	default: return 0;
	}
}

struct Node{
	char operand = ' ';
	int value;
};

bool operator<(const Node& lhs, const Node& rhs)
{
	return char2oper(lhs.operand) < char2oper(rhs.operand);
}

istream& operator>>(istream& writer, Node& node){
	writer >> node.operand >> node.value;
	return writer;
}

ostream& operator<<(ostream& reader, const Node& node){
	reader << node.operand << ' ' << node.value;
	return reader;
}

vector<Node> vector_filer(const string& input, int number){
	vector<Node> result;
	stringstream stream(input);
		while (number > 0) {
			Node node;
			stream >> node;
			result.push_back(node);
			number--;
		}
	return result;
}

inline ostream& fillStream(ostream& reader, char symbol, int number)
{
	while(number> 0){
		reader << symbol;
		number--;
	}
	return reader;
}

int scopeNeed(const vector<Node>& input){
	int counter = 0;
	for (auto it = input.begin(); it != input.end(); it++){
		if ( next(it) == input.end())
			return counter;
		if ( *it < *next(it))
			counter++;
	}
	return counter;
}

class LocExpression
{
public:
	LocExpression(const string& input, int number, int first)
	{
		_nodes = vector_filer(input, number);
		stringstream writer;
		int scope_number = scopeNeed(_nodes);
		fillStream(writer, '(', scope_number);
		writer << first;
		for ( auto it = _nodes.begin(); it != _nodes.end(); it++)
		{
			if ( next(it) != _nodes.end()){
				writer << ' ' <<  *it;
				if ( *it < *next(it)){
					writer << ')';
				}
			} else{
				writer << ' ' << *prev(_nodes.end());
			}
		}
		_expression = writer.str();
	}
	vector<Node> _nodes;
	vector<bool> scopable;
	string _expression;
};

ostream& operator<<(ostream& reader,const LocExpression& expr){
	reader << expr._expression;
	return reader;
}
#endif // LOCONIC_NUMERIC_EXPRESSION_H
