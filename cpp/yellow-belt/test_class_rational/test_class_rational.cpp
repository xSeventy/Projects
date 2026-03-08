#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <set>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <exception>
#include <cassert>

 
using namespace std;



template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
      os << "{";
      bool first = true;
      for (const auto& x : s) {
        if (!first) {
          os << ", ";
        }
        first = false;
        os << x;
      }
      return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
      os << "{";
      bool first = true;
      for (const auto& x : s) {
        if (!first) {
          os << ", ";
        }
        first = false;
        os << x;
      }
      return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
      os << "{";
      bool first = true;
      for (const auto& kv : m) {
        if (!first) {
          os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
      }
      return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
      if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
           os << " hint: " << hint;
        }
        throw runtime_error(os.str());
      }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
      template <class TestFunc>
      void RunTest(TestFunc func, const string& test_name) {
        try {
          func();
          cerr << test_name << " OK" << endl;
        } catch (exception& e) {
          ++fail_count;
          cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
          ++fail_count;
          cerr << "Unknown exception caught" << endl;
        }
      }

      ~TestRunner() {
        if (fail_count > 0) {
          cerr << fail_count << " unit tests failed. Terminate" << endl;
          exit(1);
        }
      }

private:
    int fail_count = 0;
};

int GCD(int a, int b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return abs(a);
}

class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        p = numerator;
        q = denominator;

        p = p / GCD(numerator, denominator);
        q = q / GCD(numerator, denominator);


        if (q < 0) {
            q = abs(q);
            p = -p;
        } else if (p == 0) {
            q = 1;
        }
    }

  int Numerator() const {
      return p;
  }

  int Denominator() const {
      return q;
  }

private:
    int p, q;
};

void TestAll() {
    Rational r;
    AssertEqual(r.Numerator(), 0, "second");
    AssertEqual(r.Denominator(), 1, "first");

    Rational ra(3, 6);
    AssertEqual(ra.Numerator(), 1, "third");
    AssertEqual(ra.Denominator(), 2, "fourth");
    
    Rational rat(3, -6);
    AssertEqual(rat.Numerator(), -1, "fifth");
    AssertEqual(rat.Denominator(), 2, "sixth");
    
    Rational rati(-3, -6);
    AssertEqual(rati.Numerator(), 1, "seventh");
    AssertEqual(rati.Denominator(), 2, "eighth");
    
    Rational ratio(0, -5);
    AssertEqual(ratio.Numerator(), 0, "nineth");
    AssertEqual(ratio.Denominator(), 1, "tenth");
    
    //Rational ration(6, 7);
    //AssertEqual(ration.Numerator(), 6, "eleventh");
    //AssertEqual(ration.Denominator(), 7, "twelveth");
    //
    //Rational rationa(-3, 6);
    //AssertEqual(rationa.Numerator(), -1, "thirteenth");
    //AssertEqual(rationa.Denominator(), 2, "fourteenth");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
    runner.RunTest(TestAll, "TestAll");
  return 0;
}


