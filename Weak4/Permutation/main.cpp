#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


vector<int> SpecialVectorFactory(int N)
{
	if (N <= 0)
		return {};
	size_t Number = static_cast<size_t>(N);
	vector<int> result(Number);
	for ( size_t i = Number; i > 0; i--){
		result[Number - i]  = static_cast<int>( i );
	}
	return result;
}
void ShowAllPermutation(ostream& reader, int N)
{
	vector<int> init = SpecialVectorFactory(N);
	if (init.empty())
		return;
	do{
		for(const auto& item: init){
			reader << item << ' ';
		}
		reader << endl;
	} while( next_permutation( 	init.begin(),
															init.end(),
															[](const int lhs, const int rhs ){
																return lhs > rhs;
															}
														)
		);

}

int main()
{
	int Number;
	cin >> Number;
	ShowAllPermutation(cout, Number);
	return 0;
}
