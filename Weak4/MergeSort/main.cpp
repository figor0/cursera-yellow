#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ( range_end - range_begin < 2){
		return;
	}
	std::vector<typename RandomIt::value_type>
			elements( range_begin, range_end );
	RandomIt left_sight = elements.begin() + (elements.end() - elements.begin())/3;
	RandomIt right_sight = elements.begin()
			+ (elements.end() - elements.begin()) * 2 / 3;
	MergeSort( elements.begin(), left_sight );
	MergeSort( left_sight, right_sight );
	MergeSort( right_sight, elements.end() );
	std::vector<typename RandomIt::value_type> tmpVector;
	std::merge(		elements.begin(),  							left_sight,
								left_sight, 											right_sight,
								std::back_inserter(tmpVector)								);
	std::merge(		tmpVector.begin(),  						tmpVector.end(),
								right_sight, 										elements.end(),
								range_begin																				);
}

int main() {
	if (system("./test_cursera")){
		return 1;
	}
	return 0;
}
