#include "date.h"

 Date::Date(int new_year, int new_month, int new_day) {
	year = new_year;
	if (new_month > 12 || new_month < 1) {
	  throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1) {
	  throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
	}
	day = new_day;
 }

std::ostream& operator<<(std::ostream& reader, const Date& date)
{
	reader << std::setfill('0') << std::setw(4) << date.GetYear() <<'-'
				 << std::setw(2) << date.GetMonth() << '-'
				 << std::setw(2) << date.GetDay();
	return reader;
}

Date ParseDate(const std::string& date) {
  std::istringstream date_stream(date);
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);
  ok = ok && date_stream.eof();

  if (!ok) {
	throw std::logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
}

Date ParseDate(std::istringstream& filler)
{
	std::string date;
	filler >> date;
	return ParseDate(date);
}

bool operator<(const Date& lhs, const Date& rhs) {
  return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <=
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date& lhs, const Date& rhs) {
  return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>=(const Date& lhs, const Date& rhs) {
  return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >=
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date& lhs, const Date& rhs) {
  return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return std::tuple{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} !=
	  std::tuple{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
