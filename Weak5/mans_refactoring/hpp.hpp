
class Person{
public:
	Person(const string& name):
		_name(name) {}
	virtual void Walk(const string& destination) const{
		cout << GetType() << ": " << GetName() << " walks to: " << destination << endl;
	}
	string GetName() const{
		return _name;
	}
	virtual string GetType() const {
		return "Person";
	}
private:
	string _name;
};

class Student: public Person {
public:

		Student(	const string& name, const string& favouriteSong): Person (name),
																																	_favouriteSong (favouriteSong)
		{}
		void Learn() {
				cout << GetType() << ": " << GetName() << " learns" << endl;
		}
		void SingSong() const{
				cout << GetType() << ": " << GetName() << " sings a song: " << _favouriteSong << endl;
		}
		void Walk(const string& destination) const override{
				Person::Walk(destination);
				SingSong();
		}
		string GetType() const override{
			return "Student";
		}
private:
		string _favouriteSong;
};

class Teacher: public Person{
public:
		Teacher(string name, string subject):
		Person(name), _subject(subject) {}
		void Teach() {
				cout << GetType() << ": " << GetName() << " teaches: " << _subject << endl;
		}
		string GetType() const override{
			return "Teacher";
		}
private:
		string _subject;
};

class Policeman: public Person {
public:
		Policeman(string name): Person(name) {}
		string GetType() const override{
			return "Policeman";
		}
		void Check(const Person& p) {
				cout << GetType() 		<< ": " << GetName() << " checks " 		<<
									p.GetType() << ". "	<< p.GetType()	<<	"'s name is: " << p.GetName() << endl;
		}
};

void VisitPlaces(const Person& person, vector<string> places) {
		for (const auto& place: places) {
			person.Walk(place);
		}
}

