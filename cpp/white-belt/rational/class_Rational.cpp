#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <stdexcept>


using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
        
        if (denominator == 0) {
                   throw invalid_argument("Denominator equals 0");
               }
        
        p = numerator;
        q = denominator;
        
        numerator = abs(numerator);
        denominator = abs(denominator);
        
        while(numerator > 0 && denominator > 0) {
            if(numerator > denominator) {
                numerator = numerator % denominator;
            } else {
                denominator = denominator % numerator;
            }
        }
         
        p = p / (denominator + numerator);
        q = q / (denominator + numerator);
    
        
        //cout << p << " " << q << "\n";
        
        if(p < 0 && q < 0) {
            p = abs(p);
            q = abs(q);
        } else if(p > 0 && q < 0) {
            q = abs(q);
            p = -p;
        } else if(p == 0 && q != 1) {
            q = 1;
        }
    }

    int Numerator() const {
        // Реализуйте этот метод
        return p;
    }

    int Denominator() const {
        // Реализуйте этот метод
        return q;
    }

    
private:
    // Добавьте поля
    int p, q;
};



Rational operator + (const Rational& lhs, const Rational& rhs) {
    int x = rhs.Denominator() * lhs.Numerator() + rhs.Numerator() * lhs.Denominator();
    int y = lhs.Denominator() * rhs.Denominator();
    Rational rat(x, y);
    return rat;
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    int x = rhs.Denominator() * lhs.Numerator() - rhs.Numerator() * lhs.Denominator();
    int y = lhs.Denominator() * rhs.Denominator();
    Rational rat(x, y);
    return rat;
}

bool operator == (const Rational& lhs, const Rational& rhs) {
    if(lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
        return true;
    } else {
        return false;
    }
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    int x = lhs.Numerator() * rhs.Numerator();
    int y = lhs.Denominator() * rhs.Denominator();
    Rational rat(x, y);
    return rat;
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    int x = lhs.Numerator() * rhs.Denominator();
    int y = lhs.Denominator() * rhs.Numerator();
    Rational rat(x, y);
    return rat;
}

bool operator < (const Rational lhs, const Rational rhs) {
    if(lhs.Numerator() * (rhs.Denominator()) < rhs.Numerator() * lhs.Denominator()) {
        return true;
    } else {
        return false;
    }
}

ostream& operator << (ostream& stream, const Rational& rational) {
    int x = rational.Numerator();
    int y = rational.Denominator();
    
    stream << x << "/" << y;
    
    return stream;
}

istream& operator >> (istream& stream, Rational& rational) {
    int x = rational.Numerator();
    int y = rational.Denominator();
    
    stream >> x;
    stream.ignore(1);
    stream >> y;
     
    rational = Rational(x, y);
    
    return stream;
}


int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}











