#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Функция для вычисления Юлианской даты (JDN)
int JDN(const string& x) {
    stringstream ss(x);
    int year, month, day, y, a, m, jdn;
    ss >> year;
    ss.ignore(1);
    ss >> month;
    ss.ignore(1);
    ss >> day;
    
    a = (14 - month) / 12;
    y = year + 4800 - a;
    m = month + 12 * a - 3;
    jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn;
}

int main() {
    map<int, long long> m;

    int E;
    cin >> E;

    // Чтение заработков
    for (int i = 0; i < E; i++) {
        string date;
        long long value;
        cin >> date >> value;
        int d = JDN(date);
        m[d] += value;
    }

    // Создание вектора дат и сумм для префиксных сумм
    vector<int> days;
    vector<long long> sums;

    // Сортируем даты, которые есть в мапе
    for (const auto& entry : m) {
        days.push_back(entry.first);
        sums.push_back(entry.second);
    }

    // Применяем partial_sum для накопленных сумм
    partial_sum(sums.begin(), sums.end(), sums.begin());

    int Q;
    cin >> Q;

    // Чтение запросов и обработка прибыли
    for (int i = 0; i < Q; i++) {
        string date1, date2;
        cin >> date1 >> date2;

        int d1 = JDN(date1);
        int d2 = JDN(date2);

        // Ищем индекс начала диапазона (включительно)
        auto it1 = lower_bound(days.begin(), days.end(), d1);
        // Ищем индекс конца диапазона (включительно)
        auto it2 = lower_bound(days.begin(), days.end(), d2);

        // Индексы для доступа к префиксным суммам
        int idx1 = it1 - days.begin();
        int idx2 = it2 - days.begin();

        // Если диапазон полностью включает дату d2
        if (idx2 < days.size() && days[idx2] == d2) {
            cout << sums[idx2] - (idx1 == 0 ? 0 : sums[idx1 - 1]) << endl;
        } else {
            cout << (idx2 == 0 ? 0 : sums[idx2 - 1]) - (idx1 == 0 ? 0 : sums[idx1 - 1]) << endl;
        }
    }

    return 0;
}
