#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "test_framework.h"
#include "mergeSort3.h"
using namespace std;

void TestAll(){
	TestRunner tr;
//	tr.RunTest
}
int main()
{
	for(int i = 5; i > 0; i--){
		// fill the vectors with random numbers
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> dis(-100, 100);

		std::vector<int> v1(9), v2(10);
		std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
//		std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));
		// init
		std::cout << "init:   ";
		std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
		// Use merge
		MergeSort(v1.begin(), v1.end());
		// output
		std::cout << "result: ";
		std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
	}
}
