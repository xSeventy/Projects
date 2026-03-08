##Декомпозиция программы: разбиение на файлы

В задаче «Декомпозиция программы» мы уже разбили монолитный код на набор функций и классов. Теперь нужно сделать следующий шаг — разделить программу на несколько файлов.

Что нужно сделать

Необходимо создать проект, состоящий из следующих файлов.

##1. query.h

В этот файл нужно поместить:

enum class QueryType

struct Query

объявление оператора ввода: istream& operator>>(istream& is, Query& q);

##2. query.cpp

В этот файл нужно поместить:

определение оператора ввода istream& operator>>(istream& is, Query& q);

##3. responses.h

В этот файл нужно поместить:

struct BusesForStopResponse

объявление оператора вывода ostream& operator<<(ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse

объявление оператора вывода ostream& operator<<(ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse

объявление оператора вывода ostream& operator<<(ostream& os, const AllBusesResponse& r);

##4. responses.cpp

В этот файл нужно поместить определения всего, что объявлено в responses.h.

##5. bus_manager.h

В этот файл нужно поместить объявление класса BusManager.

##6. bus_manager.cpp

В этот файл нужно поместить определения методов класса BusManager.

##7. main.cpp

В этот файл нужно поместить функцию main.

