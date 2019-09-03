//#include "test_framework.h"
#include <string>

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
		const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u
			 << " hint: " << hint;
		throw runtime_error(os.str());
	}
}

inline void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

void TestDefaultConstructor()
{
	Rational r;
	Assert(r.Numerator() == 0 && r.Denominator() == 1, "Default constructor wrong work");
}

void TestCompression()
{
	{
		Rational r(4, 12);
		Assert(r.Numerator() == 1
			&& r.Denominator() == 3,
			"Compression wrong work");
	}
}

void TestMinus()
{
	{
		Rational r(4, - 12);
		Assert(r.Numerator() == -1
			&& r.Denominator() == 3,
			"Compression wrong work");
	}
	{
		Rational r(-4, -12);
		Assert(r.Numerator() == 1
			&& r.Denominator() == 3,
			"Compression wrong work");
	}
	{
		Rational r(- 4, 12);
		Assert(r.Numerator() == -1
			&& r.Denominator() == 3,
			"Compression wrong work");
	}
	{
		Rational r(1, 3);
		Assert(r.Numerator() == 1
			&& r.Denominator() == 3,
			"Compression wrong work");
	}
}
void TestZero()
{
	{
		Rational r(0, 20);
		Assert(r.Numerator() == 0
			&& r.Denominator() == 1,
			"Zero wrong work");
	}

}

void testAll()
{
	TestRunner tr;
	tr.RunTest(TestDefaultConstructor, "Wrong default constructor");
	tr.RunTest( TestCompression, "Compression");
	tr.RunTest( TestMinus, "Minus interpretator");
	tr.RunTest( TestZero, "Zero work");
}


int main(){
	testAll();
	return 0;
}
