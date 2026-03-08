#pragma once
#include <string>
#include <iostream>
#include <vector>


enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  std::string bus, stop;
  std::vector<string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);
