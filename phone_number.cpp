#include <algorithm>
#include <stdexcept>
#include <vector>

#include "phone_number.h"

vector<string> split(string input)
{
	vector<string> result;
	if ( !input.empty()){
		for (auto it = input.begin(); it != input.end(); it++) {
			if ( *it == '-'){
				if (it - input.begin() > 1)
					result.push_back({input.begin(), it});
				if (next(it) == input.end())
					break;
				input.erase(input.begin(), next(it));
				it = input.begin();
			}
		}
	}
	if ( !input.empty()){
		result.push_back(input);
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
	vector<string> separeted = split(international_number);
	if (separeted.size() != 3 && separeted.size() != 5)
		throw err;
	country_code_ = separeted[0];
	city_code_ = separeted[1];
	local_number_ = separeted[2];
}

string PhoneNumber::GetCountryCode() const{ return country_code_;}
string PhoneNumber::GetCityCode() const{ return city_code_;}
string PhoneNumber::GetLocalNumber() const{ return local_number_;}
string PhoneNumber::GetInternationalNumber() const{ return country_code_;}


















