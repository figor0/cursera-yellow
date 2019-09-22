#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <list>
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>

#include "date.h"
#include "node.h"
#include "condition_parser.h"
using vecIt = vector<string>::iterator;
using Events = std::pair<Date, vector<std::string>>;
using Event = std::pair<Date, std::string>;

class Database
{
	using Predicate = std::function<bool(const Date&, const std::string&)>;
	using EventIt = std::map<Date, std::vector<std::string>>;
public:
	void 	Add		(const 	Date& 			date, 		const std::string& event);
	ostream& 	Print	(std::ostream& 	print_stream);
	int 	RemoveIf(const 	Predicate& 		predicate	);
	std::list<Event> FindIf(const Predicate& predicate	);
	Event 	Last	(const Date& date);
private:
	std::map<Date, std::vector<std::string>> _events;
};

template<typename T>
ostream& operator<<(ostream& reader, const vector<T>& values){
	for (auto it = values.begin(); it != values.end(); it++){
		reader << *it;
		if (next(it) != values.end())
			reader << ' ';
	}
	return reader;
}

template <typename First, typename Second>
ostream& operator<<(ostream& reader, const pair<First, Second>& value)
{
	reader << value.first << " " << value.second;
	return reader;
}

#endif // DATABASE_H
