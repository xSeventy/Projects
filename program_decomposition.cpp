/*
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
ALL_BUSES — вывести список всех маршрутов с остановками.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cassert>


using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
    string command;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        int stop_count;
        is >> q.bus >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
          is >> stop;
        }
    } else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
      bus_stops[bus] = stops;
      for(const auto& x : stops) {
          stop_buses[x].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
      BusesForStopResponse response;
      if (stop_buses.count(stop)) {
          response.stop_buses = stop_buses.at(stop);  // Используем at() для доступа в const методе
      } else {
        response.stop_buses = {};  // Пустой вектор, если остановка не найдена
      }
      return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
      StopsForBusResponse response;
      response.bus = bus;  // Сохраняем имя автобуса в структуре
          if (bus_stops.count(bus)) {
              response.bus_stops = bus_stops.at(bus);  // Список остановок для автобуса
              for (const auto& stop : response.bus_stops) {
                  // Сохраняем только автобусы для каждой остановки текущего автобуса
                  response.stop_buses[stop] = stop_buses.at(stop);
              }
          }
          return response;
  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse response;
    response.bus_stops = bus_stops;
    return response;
  }
private:
    map<string, vector<string>> bus_stops;
    map<string, vector<string>> stop_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
