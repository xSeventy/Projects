#pragma once
#include <iosfwd>



class Date {
private:
    int year, month, day;
    
public:
    
    Date(const int& y, const int& m, const int& d);
    
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    
};

std::ostream& operator<<(std::ostream& os, const Date& d);

Date ParseDate(std::istream& istr);

bool operator < (const Date& a, const Date& b);
bool operator <= (const Date& a, const Date& b);
bool operator == (const Date& a, const Date& b);
bool operator != (const Date& a, const Date& b);
bool operator > (const Date& a, const Date& b);
bool operator >= (const Date& a, const Date& b);

