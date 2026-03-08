#include <utility>
#include <memory>
#include <deque>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "profile.h"

using namespace std;

double pi = 3.14;

class Figure {
public:
    

    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
    
};

class Triangle : public Figure {
public:
    
    Triangle(double& a, double& b, double& c) : a_(a), b_(b), c_(c) {}
    
    string Name() const override {
        return "TRIANGLE";
    }
    
    double Perimeter() const override {
        return a_ + b_ + c_;
    }
    
    double Area() const override {
        double p = (a_ + b_ + c_) / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
    
     const double a_, b_, c_;
};

class Rect : public Figure {
public:
    Rect(double& a, double& b) : a_(a), b_(b) {}
    
    string Name() const override {
        return "RECT";
    }
    
    double Perimeter() const override {
        return 2 * (a_ + b_);
    }
    
    double Area() const override {
        return a_ * b_;
    }
    
    
    double a_, b_;
};

class Circle : public Figure {
public:
    
    Circle(double& r) : r_(r) {}
    
    string Name() const override {
        return "CIRCLE";
    }
    
    double Perimeter() const override {
        return 2.0 * pi * r_;
    }
    
    double Area() const override {
        return pi * r_ * r_;
    }
    
    double r_;
};

shared_ptr<Figure> CreateFigure (istream& ss) {
    string fig;
    ss >> fig;
    if(fig == "RECT") {
        double a, b;
        ss >> a >> b;
        return make_shared<Rect>(a, b);
    } else if(fig == "CIRCLE") {
        double r;
        ss >> r;
        return make_shared<Circle>(r);
    } else {
        double a, b, c;
        ss >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
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
