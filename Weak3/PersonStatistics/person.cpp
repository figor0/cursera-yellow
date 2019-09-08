//#include "person.h"

using namespace std;

int CaseGender( std::vector<Person>& stats, Gender gender){
	auto resultIt = partition(stats.begin(), stats.end(),
	[gender](const Person& p){
		return p.gender == gender;
	});
	int result = ComputeMedianAge(stats.begin(), resultIt);
//	stats.erase(stats.begin(), resultIt);
	return result;
}

int CaseGenderEmployed( vector<Person>& stats,
													Gender gender, bool employed)
{
	auto resultIt = partition(stats.begin(), stats.end(),
	[gender, employed](const Person& p){
		return p.gender == gender && p.is_employed == employed;
	});
	int result = ComputeMedianAge(stats.begin(), resultIt);
//	stats.erase(stats.begin(), resultIt);
	return result;
}

void PrintStats(std::vector<Person> stats)
{
	cout <<"Median age = " <<
				 ComputeMedianAge(stats.begin(), stats.end()) << endl;
	cout <<"Median age for females = "
			<< CaseGender( stats, Gender::FEMALE ) << endl;
	cout <<"Median age for males = "
			<< CaseGender( stats, Gender::MALE) << endl;
	cout << "Median age for employed females = "
			 << CaseGenderEmployed( stats, Gender::FEMALE, true) << endl;
	cout <<"Median age for unemployed females = "
			<< CaseGenderEmployed( stats, Gender::FEMALE, false) << endl;
	cout << "Median age for employed males = "
			 << CaseGenderEmployed( stats, Gender::MALE, true) << endl;
	cout << "Median age for unemployed males = "
			 << CaseGenderEmployed( stats, Gender::MALE, false) << endl;
}

