#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iterator>

#include "phone_number.h"

vector<string> split(string::const_iterator begin,
										 string::const_iterator end,
										 char separator)
{
	vector<string> result;
	if (end - begin > 0){
		for (auto baseIt = begin, runer = begin;
				 baseIt != end;
				 runer++){
			if ( runer == end){
				result.push_back(string(baseIt, runer));
				baseIt = runer;
			}
			if ( *runer == separator){
				if ( runer - baseIt > 0){
					result.push_back(string(baseIt, runer));
				}
				else{
					result.push_back("");
				}
				baseIt = next(runer);
			}
		}
	}
	return result;
}

PhoneNumber::PhoneNumber(const string &international_number)
{
	string copy = international_number;
	invalid_argument err("");
	if (international_number.empty())
		throw err;
	if (international_number[0] != '+')
		throw err;
	vector<string> separeted = split( international_number.begin() + 1,
																international_number.end(), '-');

	bool emptyable = any_of(separeted.begin(), separeted.end(), [](string value){
		return value.empty();
	});
	if ( emptyable )
		throw err;
	if ( separeted.size() < 3 || separeted.size() > 5)
		throw err;
	country_code_ = separeted[0];
	city_code_ = separeted[1];
	for (size_t i = 2; i < separeted.size() ; i++){
		local_number_+= separeted[i];
		if ( separeted.size() > 3 && i != separeted.size() - 1){
			local_number_+='-';
		}
	}
}

string PhoneNumber::GetCountryCode() const{ return country_code_;}
string PhoneNumber::GetCityCode() const{ return city_code_;}
string PhoneNumber::GetLocalNumber() const{ return local_number_;}
string PhoneNumber::GetInternationalNumber() const
{
	return "+" + GetCountryCode() + "-"
			+ GetCityCode() + "-"
			+ GetLocalNumber();
}


















