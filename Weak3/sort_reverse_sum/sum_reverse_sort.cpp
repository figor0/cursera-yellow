#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y){
	return x + y;
}

string Reverse(string s){
	if ( s.empty() )
		return s;
	for (size_t i = 0; i < s.size()/2; i++){
		auto copy = s[i];
		s[i] = s[s.size() - i - 1];
		s[s.size() - i - 1] = copy;
	}
	return s;
}

//void Sort(vector<int>& nums){
//	if ( nums.empty() )
//		return;
//	int move_counter = 0;
//	bool first = true;
//	while ( move_counter != 0 || first == true) {
//		move_counter = 0;
//		if (first){
//			first = false;
//		}
//		for (auto It = nums.begin(); It != nums.end(); It++) {
//			if ( It + 1 != nums.end()){
//				if ( *It > *(It+1) ){
//					int copy = *It;
//					*It = *(It+1);
//					*(It+1) = copy;
//					move_counter++;
//				}
//			}
//		}
//	}
//}

void Sort(vector<int>& nums){
	sort(nums.begin(), nums.end());
}
