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
#include <set>

#include "date.h"
#include "node.h"
#include "condition_parser.h"

class Events4Date{
public:
	using events_it = set<string>::iterator;
	using Events4Date_it = vector<events_it>::iterator;
	pair<events_it, bool> insert(const string& value){
		auto [it, flag] = _events.insert(value);
		if ( flag == true){
			_events_order.push_back(it);
		}
		return {it, flag};
	}
	void erase( Events4Date_it begin, Events4Date_it end){
		auto begin_copy = begin;
		while ( begin_copy != end ){
			_events.erase(*begin_copy);
			begin_copy++;
		}
		_events_order.erase(begin, end);
	}
	bool empty() const { return _events_order.empty() && _events.empty(); }
	size_t size() const { return _events_order.size() + _events.size(); }
	std::set<string> _events;
	std::vector<events_it> _events_order;
};

class Database
{
	using Predicate = std::function<bool(const Date&, const std::string&)>;
	using EventIt = std::map<Date, std::vector<std::string>>;
	using Event = std::pair<Date, std::string>;
public:
	void 	Add		(const 	Date& 			date, 		const std::string& event);
	ostream& 	Print	(std::ostream& 	print_stream) const;
	int 	RemoveIf(const 	Predicate& 		predicate	);
	std::list<Event> FindIf(const Predicate& predicate	) const;
	Event 	Last	(const Date& date) const;
private:
	map<Date, Events4Date> _events;
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
