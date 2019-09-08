#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "person.h"

using namespace std;

int main() {
	if (system("./test_cursera")){
		return 1;
	}
	vector<Person> persons = {
			{31, Gender::MALE, false},
			{40, Gender::FEMALE, true},
			{24, Gender::MALE, true},
			{20, Gender::FEMALE, true},
			{80, Gender::FEMALE, false},
			{78, Gender::MALE, false},
			{10, Gender::FEMALE, false},
			{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}
