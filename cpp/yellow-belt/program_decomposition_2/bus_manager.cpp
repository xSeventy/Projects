#include "bus_manager.h"



  void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
      bus_stops[bus] = stops;
      for(const auto& x : stops) {
          stop_buses[x].push_back(bus);
      }
  }

  BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
      BusesForStopResponse response;
      if (stop_buses.count(stop)) {
          response.stop_buses = stop_buses.at(stop);  // Используем at() для доступа в const методе
      } else {
        response.stop_buses = {};  // Пустой вектор, если остановка не найдена
      }
      return response;
  }

  StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse response;
    response.bus_stops = bus_stops;
    return response;
  }

