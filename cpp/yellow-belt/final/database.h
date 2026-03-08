#pragma once
#include "date.h"
#include <unordered_set>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>
#include <tuple>
#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>

bool operator < (const Date& lhs, const Date& rhs);

class Database {
public:
    
    void Add(const Date& d, const string& event);
    
    void Print(ostream& os) const;
    
    template<typename Predicate>
    int RemoveIf(Predicate pred);
    
    template <typename Predicate>
    std::vector<std::pair<Date, std::string>>
    FindIf(Predicate pred) const;
    
    string Last(const Date& d) const;
    
private:
    map<Date, vector<string>> events;
    map<Date, unordered_set<string>> events_s;
};

template <typename Predicate>
int Database::RemoveIf(Predicate pred) {
    int counter = 0;

    for (auto it = events.begin(); it != events.end(); ) {
        const Date& d = it->first;
        auto& vec = it->second;

        // set для этой даты должен существовать, но берём аккуратно
        auto sit = events_s.find(d);
        // если вдруг не нашли — можно считать, что uniq пустой
        // (но по инварианту должен быть)
        auto* s = (sit == events_s.end() ? nullptr : &sit->second);

        auto new_end = std::remove_if(vec.begin(), vec.end(),
            [&](const std::string& e) {
                if (pred(d, e)) {
                    ++counter;
                    if (s) s->erase(e);   // чистим uniq
                    return true;
                }
                return false;
            }
        );

        vec.erase(new_end, vec.end());

        if (vec.empty()) {
            // убираем и uniq по дате тоже
            events_s.erase(d);
            it = events.erase(it);
        } else {
            ++it;
        }
    }

    return counter;
}

template <typename Predicate>
std::vector<std::pair<Date, std::string>>
Database::FindIf(Predicate pred) const {
    std::vector<std::pair<Date, std::string>> result;

    for (const auto& [d, vec] : events) {
        for (const auto& e : vec) {
            if (pred(d, e)) {
                result.push_back({d, e});
            }
        }
    }
    return result;
}
