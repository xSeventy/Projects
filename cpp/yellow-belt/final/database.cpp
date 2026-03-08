#include "database.h"
#include "date.h"

void Database::Add(const Date& d, const string& event) {
    auto& s = events_s[d];
        if (s.insert(event).second) {           
            events[d].push_back(event);
        }
}

void Database::Print(ostream& os) const {       // События в рамках одной даты необходимо выводить в порядке добавления
    for(const auto& x : events) {
        for(const auto& y : x.second) {
              os << setw(4) << setfill('0') << x.first.GetYear()  << '-'
                 << setw(2) << setfill('0') << x.first.GetMonth() << '-'
                 << setw(2) << setfill('0') << x.first.GetDay()   << " "
                 << y << endl;
        }
    }
}

string Database::Last(const Date &d) const {                                      // string?
    auto it = events.upper_bound(d);
    if(it == events.begin()) {
        throw invalid_argument("No entries");
    }
    
    it--;
    const Date& ans = it->first;
    const vector<string>& fin = it->second;
    
    
    stringstream ss;
    ss  << setw(4) << setfill('0') << ans.GetYear()  << '-'
        << setw(2) << setfill('0') << ans.GetMonth() << '-'
        << setw(2) << setfill('0') << ans.GetDay()   << " "
        << fin.back();
    
    string res = ss.str();
    
    return res;
}


    


