#include "date.h"
#include <sstream>
#include <iomanip>


Date::Date(const int& y, const int& m, const int& d) : year(y), month(m), day(d) {}

int Date::GetYear() const {
    return year;
}
int Date::GetMonth() const {
    return month;
}
int Date::GetDay() const {
    return day;
}

ostream& operator<<(ostream& os, const Date& d) {
    os << setw(4) << setfill('0') << d.GetYear() << '-'
       << setw(2) << setfill('0') << d.GetMonth() << '-'
       << setw(2) << setfill('0') << d.GetDay();
    return os;
}

Date ParseDate(istream& istr) {
    string date;
    istr >> date;
    istringstream is(date);
    int year, month, day;
    is >> year;
    year = abs(year);
    if(is.peek() != '-') {
        stringstream s;
        s << "Wrong date format: " << date;
        throw runtime_error(s.str());   
    }
    is.ignore(1);
    is >> month;
    month = abs(month);
    if(is.peek() != '-') {
        stringstream a;
        a << "Wrong date format: " << date;
        throw runtime_error(a.str());
    }
    is.ignore(1);
    if(is.peek() == EOF) {
        stringstream a;
        a << "Wrong date format: " << date;
        throw runtime_error(a.str());
    }
    is >> day;
    day = abs(day);
    return Date(year, month, day);
}

bool operator < (const Date& a, const Date& b) {
  return make_tuple(a.GetYear(), a.GetMonth(), a.GetDay()) <
         make_tuple(b.GetYear(), b.GetMonth(), b.GetDay());
}

bool operator == (const Date& a, const Date& b) {
  return make_tuple(a.GetYear(), a.GetMonth(), a.GetDay()) ==
         make_tuple(b.GetYear(), b.GetMonth(), b.GetDay());
}

bool operator != (const Date& a, const Date& b) { return !(a == b); }
bool operator >  (const Date& a, const Date& b) { return b < a;     }
bool operator <= (const Date& a, const Date& b) { return !(b < a);  }
bool operator >= (const Date& a, const Date& b) { return !(a < b);  }


