#include "database.h"

using events_it = set<string>::iterator;
using Event = std::pair<Date, std::string>;
using Events4Date_it = vector<events_it>::iterator;

void 	Database::Add		(const 	Date& 			date, 		const std::string& event)
{
	_events[date].insert(event);
}

ostream& Database::Print	(std::ostream& 	printer) const
{
	if (_events.empty() )
		return printer;
	for (const auto& [key, values]: _events)
	{
		for (auto it = values._events_order.begin();
				 it != values._events_order.end() ;
				 it++)
		{
			printer << key << ' ' << **it << endl;
		}
	}
	return printer;
}

int 	Database::RemoveIf(const 	Predicate& 		predicate	)
{
	using namespace std::placeholders;
	if (_events.empty())
		return 0;
	int counter = 0;
	for (auto mapIt = _events.begin(); mapIt != _events.end() ;){
		auto& date = mapIt->first;
		auto& events = mapIt->second;
		auto prepared_predicate =
				[date, predicate](events_it it){
			return predicate(date, *it);
		};
		auto result = remove_if( events._events_order.begin(),
															events._events_order.end(),
															prepared_predicate );
		counter += events._events_order.end() - result;
		events.erase( result, events._events_order.end() );
		if ( mapIt->second.size() == 0)
		{
			mapIt++;
			_events.erase( prev(mapIt) );
			if ( _events.begin() != mapIt )
				mapIt--;
		} else{
			mapIt++;
		}
	}
	if (_events.empty())
		cout << "empty" << endl;
	else
		cout << "not empty" << endl;
	return counter;
}

std::list<Event> Database::FindIf(const Predicate& predicate	) const
{
	using namespace std::placeholders;
	if (_events.empty())
		return {};
	list<Event> result;
	for (auto mapIt = _events.begin(); mapIt != _events.end() ; mapIt++){
		auto& date = mapIt->first;
		auto& events = mapIt->second._events_order;
		for ( auto eventIt: events )
		{
			if ( predicate( date, *eventIt ) )
			{
				result.push_back( {date, *eventIt} );
			}
		}
	}
	return result;
}

Event Database::Last	(const Date& date) const
{
	if (_events.empty())
		throw invalid_argument("No entries");
	auto predicate = [date](const pair<Date, Events4Date> value){
		return date >= value.first;
	};
	auto result = find_if(_events.rbegin(), _events.rend(), predicate);
//	auto result = find_if(_eventsrbegin(), _events.rend(), predicate);
	if ( result == _events.rend())
		throw invalid_argument("No entries");
	return {result->first, *(result->second._events_order.back())};
}
