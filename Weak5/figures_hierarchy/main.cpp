#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iomanip>
#include <math.h>

using namespace std;


enum class Shape{
	RECTANGLE,
	TRIANGLE,
	CIRCLE,
	FIGURE
};

class Figure{
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
private:
};

class Rect: public Figure{
public:
	Rect(int width, int heigt):
		_width(width), _height(heigt)
	{}
	string Name() const override { return "RECT"; }
	double Perimeter() const override{ return (_width + _height)*2;}
	double Area() const override{ return _width*_height;}
private:
	int _width;
	int _height;
};

class Triangle: public Figure{
public:
	Triangle(int a, int b, int c): _a(a), _b(b), _c(c){}
	string Name() const override{ return "TRIANGLE";}
	double Perimeter() const override{ return _a + _b + _c; }
	double Area() const override{
		double halfPerimetr = Perimeter()/2;
		return sqrt(halfPerimetr*(halfPerimetr - _a) * (halfPerimetr - _b) * (halfPerimetr - _c));
	}
private:
	int _a, _b, _c;
};

class Circle: public Figure{
public:
	Circle(int radius): _radius(radius) {}
	string Name() const override { return "CIRCLE"; }
	double Perimeter() const override{ return 2*3.14*_radius; }
	double Area() const override{ return 3.14*_radius*_radius; }
private:
	int _radius;
};

Shape typeParse(const string& type){
	if (type == "RECT")
		return Shape::RECTANGLE;
	else if( type == "TRIANGLE")
		return Shape::TRIANGLE;
	else if( type == "CIRCLE")
		return Shape::CIRCLE;
	else
		return Shape::FIGURE;
}

shared_ptr<Figure> CreateFigure( istringstream& filler){
	string figure_type;
	filler >> figure_type;
	switch ( typeParse(figure_type)) {
	case Shape::RECTANGLE:{
		int width, height;
		filler >> width >> height;
		return make_shared<Rect>(Rect(width, height));
	}
	case Shape::TRIANGLE:{
		int a, b, c;
		filler >> a >> b >> c;
		return make_shared<Triangle>(Triangle(a, b, c));
	}
	case Shape::CIRCLE:{
		int radius;
		filler >> radius;
		return make_shared<Circle>(Circle(radius));
	}
	default:{
		throw invalid_argument("invalid figure");
	}
	}
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
						 << current_figure->Name() << " "
						 << current_figure->Perimeter() << " "
						 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
