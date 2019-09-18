#ifndef DATE_H
#define DATE_H

#include <istream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <exception>
#include <vector>

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day);
  int GetYear() const {
	return year;
  }
  int GetMonth() const {
	return month;
  }
  int GetDay() const {
	return day;
  }

private:
  int year;
  int month;
  int day;
};

std::ostream& operator<<(std::ostream& reader, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
Date ParseDate(std::istringstream& filler);


#endif // DATE_H
