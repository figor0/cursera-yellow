#include <iostream>

//#include "buse_decomposition.h"

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;
class BusManager;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

QueryType CheckType(const string& input)
{
	if ( input == "NEW_BUS"){
		return QueryType::NewBus;
	} else if (input == "BUSES_FOR_STOP" ){
		return QueryType::BusesForStop;
	} else if ( input == "STOPS_FOR_BUS"){
		return QueryType::StopsForBus;
	} else if (input == "ALL_BUSES"){
		return QueryType::AllBuses;
	} else {
		throw invalid_argument("Wrong command");
	}
}

istream& operator >> (istream& is, Query& q) {
	string command;
	is >> command;
	q.type = CheckType(command);
	uint number;
	switch (q.type) {
	case QueryType::NewBus:
		is >> q.bus;
		is >> number;
		q.stops.resize(number);
		for (auto& item: q.stops){
			is >> item;
		}
	break;
	case QueryType::StopsForBus:
		is >> q.bus;
	break;
	case QueryType::BusesForStop:
		is >> q.stop;
	break;
	case QueryType::AllBuses:
	break;
	}
	return is;
}

struct BusesForStopResponse {
	string stop;
	vector<string> buses;
	bool empty() const{
		return stop.empty();
	}
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if ( r.empty() ) {
		os << "No stop";
	} else {
		for (const string& bus: r.buses) {
			os << bus << " ";
		}
	}
	return os;
}

struct StopsForBusResponse {
	string bus_;
	vector<string> stops_;
	map<string, vector<string>> buses_in_stop_;

	bool empty() const{
		return bus_.empty();
	}
};


ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if ( r.empty() ) {
		os << "No bus";
	} else {
		for (const string& stop : r.stops_) {
			os << "Stop " << stop << ": ";
			if ( r.buses_in_stop_.at(stop).size() == 1 ) {
				os << "no interchange";
			} else {
				for (const string& other_bus : r.buses_in_stop_.at(stop)) {
					if ( r.bus_ != other_bus ) {
						os << other_bus << " ";
					}
				}
			}
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops_;
	bool empty() const{
		return buses_to_stops_.empty();
	}
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if ( r.empty() ) {
		os << "No buses";
	} else {
		for (const auto& bus_item : r.buses_to_stops_) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		stops_to_buses_[bus] = stops;
		for ( const auto& stop: stops){
			buses_to_stops_[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		if ( buses_to_stops_.count(stop) != 0){
			return BusesForStopResponse{stop, buses_to_stops_.at(stop)};
		}
		else {
			return {};
		}
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse stops;
		if ( stops_to_buses_.count(bus) != 0){
			stops.bus_ = bus;
			stops.stops_ = stops_to_buses_.at(stops.bus_);
			for ( const auto& item: stops.stops_)
			{
				stops.buses_in_stop_[item] = buses_to_stops_.at(item);
			}
			return stops;
		}
		else return {};
	}

	AllBusesResponse GetAllBuses() const {
			return {stops_to_buses_};
	}
private:
	map<string, vector<string>> buses_to_stops_, stops_to_buses_;
};

int main() {
	if ( system("./test_cursera") )
		return 1;
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
