#ifndef DATABASE_H
#define DATABASE_H

#include "date.h"
#include "node.h"
#include "condition_parser.h"
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <list>

class Database
{
	using Predicate = std::function<bool(const Date&, const std::string&)>;
	using EventIt = std::map<Date, std::vector<std::string>>;
	using Event = std::pair<Date, std::string>;
public:
	void 	Add		(const 	Date& 			date, 		const std::string& event);
	void	Print	(		std::ostream& 	print_stream);
	int 	RemoveIf(const 	Predicate& 		predicate	);

	std::list<Event> FindIf(const Predicate& predicate	);
	void 	Last	(const Date& date);
private:
	std::map<Date, std::vector<std::string>> _events;
};
#endif // DATABASE_H
