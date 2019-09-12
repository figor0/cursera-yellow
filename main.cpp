#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

//#include "test_framework.h"
//#include "FindStartWith.h"

using namespace std;

struct cmp{
	bool operator()( const std::string& lhs, const char rhs) const
	{
		if (lhs.empty() == false)
			return lhs[0] < rhs;
		return false;
	}
	bool operator()( const char lhs, const std::string& rhs) const
	{
		if ( rhs.empty() == false)
			return lhs < rhs[0];
		return false;
	}
};

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin	,
									   RandomIt range_end	,
									   char 	prefix		)
{
	if (range_end - range_begin == 0)
		return {range_begin, range_end};
	auto pairIt = std::equal_range(range_begin, range_end, prefix, cmp{});
	return {pairIt.first,	pairIt.second};
}


int main() {
	if (system("./test_cursera")){
		return 1;
	}

  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
  const auto m_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
	cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
	  (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
	  FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
	  (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
