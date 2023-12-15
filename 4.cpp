#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
    string type_in_str;
    is >> type_in_str;
    if (type_in_str == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto &stop: q.stops) {
            is >> stop;
        }
    } else if (type_in_str == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (type_in_str == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (type_in_str == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> stop_bus;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if(r.stop_bus.empty()){
        os << "No stop";
        return os;
    }

    bool is_first = true;
    for (const auto &bus: r.stop_bus) {
        if (!is_first) {
            os << ' ';
        }
        is_first = false;
        os << bus;
    }

    return os;
}

struct StopsForBusResponse {
    vector<string> bus_stop;
    map<string, vector<string>> stop_bus;
    string bus;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if(r.bus_stop.empty()){
        os << "No bus";
        return os;
    }

    for (const auto &stop: r.bus_stop) {
        if (r.stop_bus.at(stop).size() == 1) {
            os << "Stop " << stop << ": no interchange\n";
            continue;
        }

        os << "Stop " << stop << ":";
        for (const auto &bus: r.stop_bus.at(stop)) {
            if(bus == r.bus){
                continue;
            }
            os << " " << bus;
        }
        if(!(stop == r.bus_stop.back())){
            os << '\n';
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> bus_stop;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.bus_stop.empty()) {
        os << "No buses";
        return os;
    }
    for (const auto &[bus, stops]: r.bus_stop) {
        os << "Bus " << bus << ": ";
        bool is_first = true;
        for (const auto &stop: stops) {
            if (!is_first) {
                os << ' ';
            }
            is_first = false;
            os << stop;
        }
        if (bus != r.bus_stop.rbegin()->first) {
            cout << '\n';
        }

    }
    return os;
}

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops) {
        for (const auto &stop: stops) {
            stop_for_bus[stop].push_back(bus);
        }
        buses_for_stop[bus] = stops;
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const {
        BusesForStopResponse get_bus_for_stop;
        if(stop_for_bus.count(stop)){
            get_bus_for_stop.stop_bus = stop_for_bus.at(stop);
        }
        return get_bus_for_stop;
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const {
        StopsForBusResponse get_stop_for_bus;
        if(buses_for_stop.count(bus)){
            get_stop_for_bus.bus_stop = buses_for_stop.at(bus);
            get_stop_for_bus.stop_bus = stop_for_bus;
            get_stop_for_bus.bus = bus;
        }
        return get_stop_for_bus;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse all_busses;
        all_busses.bus_stop = buses_for_stop;
        return all_busses;
    }

private:
    map<string, vector<string>> stop_for_bus;
    map<string, vector<string>> buses_for_stop;
};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

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
}