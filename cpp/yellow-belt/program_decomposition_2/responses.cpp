#include "responses.h"



struct BusesForStopResponse {
  // Наполните полями эту структуру
    vector<string> stop_buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
    if(r.stop_buses.size() > 0) {
        for(const auto& x : r.stop_buses) {
            os << x << " ";
        }
    } else {
        os << "No stop";
    }
    return os;
}

struct StopsForBusResponse {
  // Наполните полями эту структуру
    map<string, vector<string>> stop_buses;
    vector<string> bus_stops;
    string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  // Реализуйте эту функцию
    if (r.bus_stops.empty()) {
            os << "No bus";
        } else {
            for (const auto& stop : r.bus_stops) {
                os << "Stop " << stop << ":";
                if (r.stop_buses.count(stop) == 0 || r.stop_buses.at(stop).size() == 1) {
                    os << " no interchange" << endl;
                } else {
                    for (const string& other_bus : r.stop_buses.at(stop)) {
                        if (r.bus != other_bus) {
                            os << " " << other_bus;
                        }
                    }
                    os << endl;
                }
            }
        }
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
    map<string, vector<string>> bus_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
    if(r.bus_stops.empty()) {
        os << "No buses";
    } else {
        for(const auto& x : r.bus_stops) {
            os << "Bus " << x.first << ":";
            for(const auto& y : x.second) {
                os << " " << y;
            }
            os << endl;
        }
    }
    return os;
}
