/*
В этой задаче вам надо разработать класс для представления рациональных чисел
и внедрить его в систему типов языка С++ так, чтобы им можно было пользоваться естественным образом
*/ 


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>

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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
            
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
