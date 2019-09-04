#include "test_framework.h"
#include "sum_reverse_sort.h"


void SumTest()
{
	Assert(Sum(-1, -4) == -5, "All negative numbers: wrong work");
	Assert(Sum(1, 4) == 5, "All positive numbers: wrong work");
	Assert(Sum(-1, 4) == 3, "Left negative right positive: wrong work");
	Assert(Sum(1, -4) == -3, "Left negative right positive: wrong work");
	Assert(Sum(0, 0) == 0, "All zero numbers: wrong work");
}

void ReverseTest()
{
	{
		Assert(Reverse({}) == string(), "empty case: wrong work");
	}
	{
		string reversed = Reverse("w");
		Assert( reversed == string("w"), "Single literal case: wrong answer - " + reversed);
		Assert(Reverse({"w"}) == string("w"), "Single literal case: wrong work");
	}
	{
		string reversed = Reverse("wtf");
		Assert( reversed == string("ftw"), "common case: wrong answer: " + reversed);
	}
	{
		string reversed = Reverse("carl marshal");
		Assert( reversed == string("lahsram lrac"), "common case: wrong answer: " + reversed);
	}
	{
		string reversed = Reverse("madam");
		Assert( reversed == string("madam"), "polindrom case: wrong answer: " + reversed
				+ " right : madam");
	}
}

void SortTest()
{
	{
		vector<int> sorted;
		Sort(sorted);
		Assert(vector<int>() == sorted, "Empty case: wrong work");
	}
	{
		vector<int> sorted{5};
		Sort(sorted);
		Assert(vector<int>{5} == sorted, "One element: wrong work");
	}
	{
		vector<int> sorted{-5, -5, -5, -5, -5};
		Sort(sorted);
		Assert(vector<int>{-5, -5, -5, -5, -5} == sorted, "Equal elements: wrong work");
	}
	{
		vector<int> sorted{5,4,3,2,1};
		Sort(sorted);
		Assert(vector<int>{1,2,3,4,5} == sorted, "Common case: wrong work" );
	}
}


void TestAll()
{
	TestRunner tr;
	tr.RunTest(SumTest, "Sum test");
	tr.RunTest(ReverseTest, "Reverse test");
	tr.RunTest( SortTest, "Sort test");
}



int main(){
	TestAll();
	return 0;
}
