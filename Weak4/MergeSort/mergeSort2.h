#ifndef MERGESORT2_H
#define MERGESORT2_H

#endif // MERGESORT2_H

#include <algorithm>
#include <vector>



template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ( range_end - range_begin < 2){
		return;
	}
	std::vector<typename RandomIt::value_type>
			elements( range_begin, range_end );
	RandomIt middle = elements.begin() + (elements.end() - elements.begin())/2;
	MergeSort( elements.begin(), middle );
	MergeSort( middle, elements.end() );

	std::merge(	elements.begin(), 	middle,
							middle, 						elements.end(),
							range_begin												);
}
