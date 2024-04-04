#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../data_structures/Graph.h"

#ifndef DA2324_PRJ1_G07_3_DATAREADER_H
#define DA2324_PRJ1_G07_3_DATAREADER_H

enum node_type {
    reservoir,
    station,
    city
};

struct Node {
    node_type type;
    string code;

    bool operator==(const Node& other) const {
        return code == other.code;
    }
};

struct Reservoir {
    string name;
    string municipality;
    int id;
    string code;
    int maxDelivery;
};

struct Station {
    int id;
    string code;
};

struct City {
    string name;
    int id;
    string code;
    int demand;
    int population;
};

struct Pipe {
    Node source;
    Node destination;
    int capacity;
    int direction;
};

class DataReader {
public:
    void loadData();
    vector<string> splitString(const string& s, char delimiter);
    void loadReservoirs(const string& reservoirFile);
    void loadStations(const string& stationFile);
    void loadCities(const string& citiesFile);
    void loadPipes(const string& pipesFile);
    const unordered_map<string, Reservoir>* getReservoirsMap() const;
    const unordered_map<string, Station>* getStationsMap() const;
    const unordered_map<string, City>* getCitiesMap() const;
    const Graph<Node>* getPipesGraph() const;

private:
    Graph<Node> PipesGraph;
    unordered_map<string, Reservoir> reservoirsMap;
    unordered_map<string, Station> stationsMap;
    unordered_map<string, City> citiesMap;
};


#endif //DA2324_PRJ1_G07_3_DATAREADER_H
