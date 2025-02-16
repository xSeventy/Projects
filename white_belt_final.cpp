/*
Необходимо написать программу на С++, которая реализует работу с простой базой данных (сокращённо «БД»). 
Программа будет общаться с пользователем через стандартный ввод и вывод (потоки stdin и stdout).

Будем хранить в нашей БД пары вида: дата, событие. 
Определим дату как строку вида Год-Месяц-День, где Год, Месяц и День — целые числа. 

Событие определим как строку из произвольных печатных символов без разделителей внутри (пробелов, табуляций и пр.).
Событие не может быть пустой строкой. В одну и ту же дату может произойти много разных событий, БД должна суметь их все сохранить. 
Одинаковые события, произошедшие в один и тот же день, сохранять не нужно: достаточно сохранить только одно из них.

Наша БД должна понимать определённые команды, чтобы с ней можно было взаимодействовать:

- добавление события:                        Add Дата Событие
- удаление события:                          Del Дата Событие
- удаление всех событий за конкретную дату:  Del Дата
- поиск событий за конкретную дату:          Find Дата
- печать всех событий за все даты:           Print
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>

using namespace std;


class Date {
public:
    
    Date(int new_year, int new_month, int new_day)
        : year(new_year), month(new_month), day(new_day) {
        if (new_month < 1 || new_month > 12) {
            throw logic_error("Month value is invalid: " + to_string(new_month));
        }
        if (new_day < 1 || new_day > 31) {
            throw logic_error("Day value is invalid: " + to_string(new_day));
        }
    }
    
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

Date ParseDate(const string& date) {
    stringstream ss(date);
    int year, month, day;
    ss >> year;
    year = abs(year);
    if(ss.peek() != '-') {
        stringstream s;
        s << "Wrong date format: " << date;
        throw runtime_error(s.str());
    }
    ss.ignore(1);
    ss >> month;
    month = abs(month);
    if(ss.peek() != '-') {
        stringstream a;
        a << "Wrong date format: " << date;
        throw runtime_error(a.str());
    }
    ss.ignore(1);
    if(ss.peek() == EOF) {
        stringstream a;
        a << "Wrong date format: " << date;
        throw runtime_error(a.str());
    }
    ss >> day;
    day = abs(day);
    if(ss.peek() != EOF) {
        stringstream a;
        a << "Wrong date format: " << date;
        throw runtime_error(a.str());
    }
    return Date(year, month, day);
}

bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    }
    if (lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetDay() < rhs.GetDay();
}

class Database {
public:
    
    void AddEvent(const Date& date, const string& event) {
        Events[date].insert(event);
    }
    
    bool DeleteEvent(const Date& date, const string& event) {
        
        if(Events[date].count(event) > 0 && Events.count(date) > 0) {
            if(Events.at(date).size() == 1) {
                Events[date].erase(event);
                Events.erase(date);
            } else {
                Events[date].erase(event);
            }
            cout << "Deleted successfully" << endl;
            return true;
        } else {
            cout << "Event not found" << endl;
            return false;
        }
    }
    
    int DeleteDate(const Date& date) {
        if (Events.count(date) > 0) {
            size_t event_count = Events[date].size();
            Events.erase(date);
            cout << "Deleted " << event_count << " events" << endl;
            return int(event_count);
        } else {
            cout << "Deleted 0 events" << endl;
            return 0;
        }
    }
    
    void Find(const Date& date) const {
        // set<string> s;
        if (Events.count(date) > 0) {
            for (const string& str : Events.at(date)) {
                cout << str << endl;
            }
        } else {
            cout << "";
        }
    }
  
    void Print() const {
        for(const auto& x : Events) {
            for(const auto& y : x.second) {
                cout << setw(4) << setfill('0') << x.first.GetYear() << '-' << setw(2) << setfill('0') << x.first.GetMonth() << '-' << setw(2)
                << setfill('0') << x.first.GetDay();
                cout << " " << y << endl;;
            }
        }
    }
    
private:
    map<Date, set<string>> Events;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // Считайте команды с потока ввода и обработайте каждую
        stringstream ss(command);
        string comm;
        ss >> comm;
        try {
            if(comm == "Add") {
                string date1, event;
                ss >> date1 >> event;
                Date date = ParseDate(date1);
                db.AddEvent(date, event);
            } else if(comm == "Del") {
                string date1, event;
                
                if(ss >> date1 >> event) {
                    ss >> date1;
                    Date date = ParseDate(date1);
                    db.DeleteEvent(date, event);
                } else {
                    ss >> date1;
                    Date date = ParseDate(date1);
                    db.DeleteDate(date);
                }
            } else if(comm == "Find") {
                set<string> s;
                string date1;
                ss >> date1;
                Date date = ParseDate(date1);
                db.Find(date);
                
            } else if(comm == "Print") {
                db.Print();
            } else if(comm.empty()) {
                continue;
            } else {
                cout << "Unknown command: " << comm << endl;
                return 1;
            }
        } catch(exception& ex) {
            cout << ex.what() << endl;
            return 1;
        }
    }
  return 0;
}
