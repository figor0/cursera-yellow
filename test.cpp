#include "buse_decomposition.h"

#include "test_framework.h"
#include <string>

void CheckTypeTest()
{
	Assert( CheckType("NEW_BUS") == QueryType::NewBus,                 "Check type case: new bus wrong");
	Assert( CheckType("BUSES_FOR_STOP") == QueryType::BusesForStop,   "Check type case: buses_for_stop wrong");
	Assert( CheckType("STOPS_FOR_BUS") == QueryType::StopsForBus,     "Check type case: stops_for_bus wrong");
	Assert( CheckType("ALL_BUSES") == QueryType::AllBuses,               "Check type case: all_buses wrong");
}

void StreamQueryWriterTest()
{
	{
		stringstream stream("NEW_BUS bus 4 stop1 stop2 stop3 stop4");
		Query q;
		stream >> q;
		Assert( q.bus == "bus", "bus name wrong");
		Assert( q.type == QueryType::NewBus, "query type wrong");
		Assert( q.stops == vector<string>{"stop1", "stop2", "stop3", "stop4"},
						"query stops wrong");
	}
	{
		stringstream stream("BUSES_FOR_STOP stop");
		Query q;
		stream >> q;
		Assert( q.stop == "stop", "stop name wrong");
		Assert( q.type == QueryType::BusesForStop, "query type wrong");
	}
	{
		stringstream stream("STOPS_FOR_BUS bus");
		Query q;
		stream >> q;
		Assert( q.bus == "bus", "bus name wrong");
		Assert( q.type == QueryType::StopsForBus, "query type wrong");
	}
	{
		stringstream stream("ALL_BUSES");
		Query q;
		stream >> q;
		Assert( q.type == QueryType::AllBuses, "query type wrong");
	}
}

void StreamReaderBusesResponseTest()
{
	{
		stringstream stream;
		stream << BusesForStopResponse{"stop", {"bus1", "bus2", "bus3"}};
		Assert(stream.str() == "bus1 bus2 bus3 ", "common case: wrong output: " +
					 stream.str());
	}
	{
		stringstream stream;
		stream << BusesForStopResponse{};
		Assert(stream.str() == "No stop", "common case: wrong output: " +
					 stream.str());
	}
}

void StreamReaderStopsForBusResponse()
{
	{
		stringstream stream;
		stream << StopsForBusResponse{};
		Assert( stream.str() == "No bus", "empty case: wrong output");
	}
	{
		stringstream stream;
		StopsForBusResponse response{
			"bus", {"stop1", "stop2", "stop3"},
			{
				{"stop1", {"bus", "bus1", "bus2"}},
				{"stop2", {"bus", "bus1", "bus2"}},
				{"stop3", {"bus"}}
			}
		};
		stream << response;
//		string result;
//		result =	string("Stop stop1: bus1 bus2 \n")
//							+ string("Stop stop2: bus1 bus2 \n")
//							+ string("Stop stop3: no interchange");
		stringstream result;
		result << "Stop stop1: bus1 bus2 \n"
					 << "Stop stop2: bus1 bus2 \n"
					 << "Stop stop3: no interchange\n";
		Assert( stream.str() == result.str(), "general case wrong:\n"
						+ stream.str() + "size = " + to_string(stream.str().size())
						+ "\nRight output:\n" + result.str() +
						" right size = " + to_string(result.str().size()));
	}
}

void emptyCheck(){
	{
		BusesForStopResponse empty;
		BusesForStopResponse notEmpty{"stop", {"bus1", "bus2", "bus3"}};
		Assert(empty.empty() == true, "BusesForStopResponse wrong not empty answer");
		Assert(notEmpty.empty() == false, "BusesForstopResponse wrong empty answer");
	}
	{
		StopsForBusResponse empty;
		StopsForBusResponse notEmpty{
			"bus", {"stop1", "stop2", "stop3"},
			{
				{"stop1", {"bus", "bus1", "bus2"}},
				{"stop2", {"bus", "bus1", "bus2"}},
				{"stop3", {"bus"}}
			}
		};

		Assert( empty.empty() == true, "StopsFofBusResponse wrong not empty answer");
		Assert( notEmpty.empty() == false, "StopsForBusResponse wrong empty answer");
	}
}

void TesGetBusesForStop()
{
}

void CheckAddBus()
{
	BusManager bm;
	bm.AddBus("bus", {"stop1" , "stop2", "stop3"});
}

void testAll(){
	TestRunner tr;
	tr.RunTest(CheckTypeTest, "CheckType test");
	tr.RunTest(StreamQueryWriterTest, "IStream >> query test");
	tr.RunTest(StreamReaderBusesResponseTest,
						 "Stream << BusesForStopResponse test");
	tr.RunTest(StreamReaderStopsForBusResponse, " << StopsForBuseResponse");
	tr.RunTest(emptyCheck, "empty test");
}
int main(){
	testAll();
	return 0;
}
