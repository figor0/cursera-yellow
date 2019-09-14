#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

//#include "test_framework.h"
//#include "FindStartWith.h"

#include <algorithm>
#include <string>
#include <utility>
#include <iterator>

using namespace std;

struct Prefix{
	Prefix(){}
	Prefix(const std::string& prefix)
		: _prefix(prefix) {}
	std::string _prefix;
};


struct stringcmp{
	bool operator()( const std::string& element, const Prefix& prefix) const
	{
		if (element.empty() == false){
			std::string element_part = std::string(element.begin(),
											  element.begin() + prefix._prefix.size());
			return element_part < prefix._prefix;
		}
		return false;
	}
	bool operator()( const Prefix& prefix, const std::string& element) const
	{
		if (element.empty() == false){
			std::string element_part = std::string(element.begin(),
											  element.begin() + prefix._prefix.size());
			return prefix._prefix < element_part;
		}
		return true;
	}
};

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	const std::string& pr)
{
	if (range_end - range_begin == 0)
		return {range_begin, range_end};
	Prefix pref(pr);
	auto durationIt = std::equal_range(range_begin, range_end, pref, stringcmp{});
	return durationIt;
}


int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
	cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
	  (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
	  (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}
