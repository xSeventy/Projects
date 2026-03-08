/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
Гарантируется, что все имена и фамилии непусты.
Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.
Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string PrintVector(const vector<string>& v) {
    if (v.empty()) {
        return "";
    }
    string result = " (";
    for (int i = v.size() - 2; i > 0; --i) {
        result += v[i] + ", ";
    }
    result += v[0] + ")";
    return result;
}

class Person {
public:
    Person(const string& birth_name, const string& birth_surname, const int& year) {
        name[year] = birth_name;
        surname[year] = birth_surname;
        birth_year = year;
    }
    
    void ChangeFirstName(int year, const string& first_name) {
        name[year] = first_name;
        
    }

    void ChangeLastName(int year, const string& last_name) {
        surname[year] = last_name;
    }

    string GetFullName(int year) const {
        string cur_name = "";
        string cur_surname = "";
        
        if(year < birth_year) {
            return "No person";
        }
        
        for (const auto& item : name) {
            if (item.first <= year) {
                cur_name = item.second;
            }
        }
        for (const auto& item : surname) {
            if (item.first <= year) {
                cur_surname = item.second;
            }
        }
        
        if (cur_name.empty() && cur_surname.empty()) {
            return "Incognito";
        } else if (!cur_name.empty() && cur_surname.empty()) {
            return cur_name + " with unknown last name";
        } else if (cur_name.empty() && !cur_surname.empty()) {
            return cur_surname + " with unknown first name";
        } else {
            return cur_name + " " + cur_surname;
        }
    }

    string GetFullNameWithHistory(int year) const {
        vector<string> name_history;
        vector<string> surname_history;
        
        string cur_name = "";
        string cur_surname = "";
        
        if(year < birth_year) {
            return "No person";
        }
        
        for (const auto& item : name) {
            if (item.first <= year) {
                if (name_history.empty() || name_history.back() != item.second) {
                    name_history.push_back(item.second);
                }
                cur_name = item.second;
            }
        }
        
        for (const auto& item : surname) {
            if (item.first <= year) {
                if (surname_history.empty() || surname_history.back() != item.second) {
                    surname_history.push_back(item.second);
                }
                cur_surname = item.second;
            }
        }

        string result;
        
        if (cur_name.empty() && cur_surname.empty()) {
            result = "Incognito";
        } else if (name_history.empty()) {
            result = cur_surname;
            if (surname_history.size() > 1) {
                result += PrintVector(surname_history);
            }
            result += " with unknown first name";
        } else if (surname_history.empty()) {
            result = cur_name;
            if (name_history.size() > 1) {
                result += PrintVector(name_history);
            }
            result += " with unknown last name";
        } else {
            result = cur_name;
            if (name_history.size() > 1) {
                result += PrintVector(name_history);
            }
            result += " " + cur_surname;
            if (surname_history.size() > 1) {
                result += PrintVector(surname_history);
            }
        }
        
        return result;
    }

private:
    map<int, string> name;
    map<int, string> surname;
    int birth_year;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967, 1959}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
    person.ChangeFirstName(1967, "Ivan");
    for (int year : {1965, 1967, 1964}) {
      cout << person.GetFullNameWithHistory(year) << endl;
    }
  return 0;
}
