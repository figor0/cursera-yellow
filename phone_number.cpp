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
				if (it - input.begin() > 0)
					result.push_back({input.begin(), prev(it)});
				input.erase(input.begin(), it);
				it = input.begin();
			}
		}
	}
	if ( !input.empty() ){
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

/*istream& operator>>(istream& stream, PhoneNumber& number)
{
	return stream;
}*/

