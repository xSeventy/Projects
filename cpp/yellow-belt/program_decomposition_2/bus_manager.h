#pragma once
#include "responses.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>


class BusManager {
private:
    std::map<string, vector<string>> bus_stops;
    std::map<string, vector<string>> stop_buses;

public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops);

    BusesForStopResponse GetBusesForStop(const std::string& stop) const;

    StopsForBusResponse GetStopsForBus(const std::string& bus) const;

    AllBusesResponse GetAllBuses() const;

};
