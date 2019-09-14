#ifndef FINDSTARTWITH_H
#define FINDSTARTWITH_H
#include <algorithm>
#include <string>
#include <utility>
#include <iterator>

/*template<typename LHS, typename RHS>
struct cmp{
	bool operator()( const LHS& lhs, const RHS& rhs) const{return lhs < rhs;}
	bool operator()( const RHS& lhs, const LHS& rhs) const{return lhs < rhs;}
};

template <>
struct cmp<std::string, char>{
	bool operator()( const std::string& lhs, const char rhs)const
	{
		return lhs[0] < rhs;
	}
};
template <>
struct cmp<char, std::string>{
	bool operator()( const char& lhs, const std::string& rhs) const
	{
		return lhs < rhs[0];
	}
};*/

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
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin	,
											 RandomIt range_end		,
											 char 	prefix			)
{
	if (range_end - range_begin == 0)
		return {range_begin, range_end};
	auto pairIt = std::equal_range(range_begin, range_end, prefix, cmp{});
	return {pairIt.first,	pairIt.second};
}

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


#endif // FINDSTARTWITH_H
