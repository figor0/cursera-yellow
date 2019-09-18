#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

enum class Comprasion{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();