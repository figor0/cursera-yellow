#include "database.h"

void 	Database::Add		(const 	Date& 			date, 		const std::string& event)
{
	if (count(_events[date].begin(), _events[date].end(), event) == 0){
		_events[date].push_back(event);
	}
}

ostream& Database::Print	(std::ostream& 	printer)
{
	for (const auto& [key, values]: _events)
	{
		for (auto it = values.begin(); it != values.end() ; it++)
		{
			printer << key << ' ' << *it;
//			if (next(it) != values.end())
				printer << endl;
		}
	}
	return printer;
}

int 	Database::RemoveIf(const 	Predicate& 		predicate	)
{
	using namespace std::placeholders;
	int counter = 0;
	for (auto mapIt = _events.begin(); mapIt != _events.end() ; mapIt++){
		auto& date = mapIt->first;
		auto& events = mapIt->second;
		std::function<bool(string)> prepared_predicate = bind( predicate, date, _1);
		auto result = remove_if(events.begin(), events.end(), prepared_predicate);
		counter += events.end() - result;
		events.erase(result, mapIt->second.end());
		if ( _events.at(date).size() == 0)
			_events.erase( date );
	}
	return counter;
}

std::list<Event> Database::FindIf(const Predicate& predicate	)
{
	using namespace std::placeholders;
	list<Event> result;
	for (auto mapIt = _events.begin(); mapIt != _events.end() ; mapIt++){
		auto& date = mapIt->first;
		auto& events = mapIt->second;
		for ( const auto& event: events )
		{
			if ( predicate( date, event ) )
			{
				result.push_back( {date, event} );
			}
		}
	}
	return result;
}

Event Database::Last	(const Date& date)
{
	auto predicate = [date](const pair<Date, vector<string>> value){
		return date >= value.first;
	};
	auto result = find_if(_events.rbegin(), _events.rend(), predicate);
	if ( result == _events.rend())
		throw invalid_argument("No entries");
	return {result->first, result->second.back()};
}
