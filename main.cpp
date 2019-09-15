#include <iostream>
#include <string>
#include <vector>

using namespace std;

using namespace std;

class Person {
public:
		Person(const string& name, const string& type) : Name(name), Type(type) {}
		virtual void Walk(const string& destination) const {}
public:
		const string Name;
		const string Type;
};

class Student : public Person {
public:

		Student(const string& name, const string& favouriteSong): Person(name, "Student"), FavouriteSong(favouriteSong) {}

		void Learn() {
				cout << "Student: " << Name << " learns" << endl;
		}

		void Walk(const string& destination)  const override {
				cout << "Student: " << Name << " walks to: " << destination << endl;
				cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
		}

		void SingSong() {
				cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
		}

public:
		const string FavouriteSong;
};


class Teacher : public Person {
public:

		Teacher(const string& name, const string& subject): Person(name, "Teacher"), Subject(subject) {}

		void Teach() {
				cout << "Teacher: " << Name << " teaches: " << Subject << endl;
		}

		void Walk(const string& destination)  const override {
				cout << "Teacher: " << Name << " walks to: " << destination << endl;
		}

public:
		const string Subject;
};


class Policeman : public Person {
public:
		Policeman(const string& name) : Person(name, "Policeman") {}

		template <typename Man>
		void Check(const Man& man) {
				string profession = typeid(man).name();
				profession.erase(0, 1);
				cout << "Policeman: " << Name << " checks " << profession << ". " << profession << "'s name is: " << man.Name << endl;
		}

		void Walk(const string& destination)  const override {
				cout << "Policeman: " << Name << " walks to: " << destination << endl;
		}
};

template <typename Man>
void VisitPlaces(const Man& man, const vector<string>& places) {
		for (auto place : places) {
				man.Walk(place);
		}
}


int main() {
		Teacher t("Jim", "Math");
		Student s("Ann", "We will rock you");
		Policeman p("Bob");

		VisitPlaces(t, {"Moscow", "London"});
		p.Check(s);
		VisitPlaces(s, {"Moscow", "London"});
		return 0;
}
