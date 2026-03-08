#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


struct BusesForStopResponse;
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
struct StopsForBusResponse;
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
struct AllBusesResponse;
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
