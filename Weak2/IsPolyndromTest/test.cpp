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





bool IsPalindrom(const string& s){

}

void CheckEasyPolyndroms()
{
	Assert(IsPalindrom("") == true, "Empty case: wrong");
	Assert(IsPalindrom("s")== true, "Single word case: wrong");
	Assert(IsPalindrom("a  a")== true, "Ignoring case: wrong");
	Assert(IsPalindrom("a/ /a")== true, "Ignoring case: wrong");
}

void CheckNotEasyPolyndroms()
{
	Assert(IsPalindrom("madam") == true, "case madam: wrong");
	Assert(IsPalindrom("level") == true, "case level: wrong");
	Assert(IsPalindrom("wasitacaroracatisaw") == true, "case wasitacaroracatisaw: wrong");
}

void CheckCommonErrors()
{
	Assert(IsPalindrom("zasitacaroracatisaw") == false, "ignoring first and last symbols");
	Assert(IsPalindrom("zasitacaroracatisa") == false, "ignoring first symbols");
	Assert(IsPalindrom("asitacaroracatisaw") == false, "ignoring last symbols");
	Assert(IsPalindrom("wasitacaboracatisaw") == false, "Last comparing befor middle of string");
	Assert(IsPalindrom("wasitasaroracatisaw") == false, "Last comparing befor middle of string");
	Assert(IsPalindrom("wasetacaroracatisaw") == false, "Last comparing befor middle of string");
}

void SpaceCheck()
{
	Assert(IsPalindrom("wasi tac aroracatis aw") == false, "case spaces: wrong");
	Assert(IsPalindrom("wasi tacaroracat isaw") == true, "case spaces descrimination");
	Assert(IsPalindrom("                   ") == true, "case spaces descrimination");
}

void WtfTest()
{
	Assert(IsPalindrom("wasiaroracatisaw") == false, "Lier true");
}

void testAll()
{
	TestRunner tr;
	tr.RunTest(CheckEasyPolyndroms, "Check easy polyndroms");
	tr.RunTest(CheckNotEasyPolyndroms, "Check not easy polyndroms");
	tr.RunTest(CheckCommonErrors, "Check Common errors");
	tr.RunTest(SpaceCheck, "Space check");
	tr.RunTest(WtfTest, "Wtf test");
}


int main(){
	testAll();
	return 0;
}
