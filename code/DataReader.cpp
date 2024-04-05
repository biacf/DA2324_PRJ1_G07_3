#include "DataReader.h"
#include <iostream>

vector<string> DataReader::splitString(const string& s, char delimiter){
    vector<string> tokens;
    istringstream tokenStream(s);
    string token;
    while(getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

void DataReader::loadReservoirs(const string& reservoirFile) {
    ifstream file(reservoirFile);
    if(!file.is_open()){
        cerr << "error opening the file" << reservoirFile << endl;
        return;
    }
    string line;
    getline(file, line);
    while(getline(file, line)){
        vector<string> tokens = splitString(line, ',');
        if(tokens.size() == 5){
            string name = tokens[0];
            string municipality = tokens[1];
            int id = stoi(tokens[2]);
            string code = tokens[3];
            int maxDelivery = stoi(tokens[4]);

            Reservoir reservoir{name, municipality, id, code, maxDelivery};

            reservoirsMap[code] = reservoir;
        }
    }
    file.close();
}

void DataReader::loadStations(const std::string &stationFile) {
    ifstream file(stationFile);
    if(!file.is_open()){
        cerr << "error opening the file" << stationFile << endl;
        return;
    }
    string line;
    getline(file, line);
    while(getline(file, line)){
        vector<string> tokens = splitString(line, ',');
        if(tokens.size() == 2){
            int id = stoi(tokens[0]);
            string code = tokens[1];

            Station station{id, code};

            stationsMap[code] = station;
        }
    }
    file.close();
}

void DataReader::loadCities(const std::string &citiesFile) {
    ifstream file(citiesFile);
    if(!file.is_open()){
        cerr << "error opening the file" << citiesFile << endl;
        return;
    }
    string line;
    getline(file, line);
    while(getline(file, line)){
        vector<string> tokens = splitString(line, ',');
        if(tokens.size() == 5){
            string name = tokens[0];
            int id = stoi(tokens[1]);
            string code = tokens[2];
            int demand = stoi(tokens[3]);
            int population = stoi(tokens[4]);

            City city{name, id, code, demand, population};

            citiesMap[code] = city;
        }
    }
    file.close();
}

void DataReader::loadPipes(const std::string &pipesFile) {
    ifstream file(pipesFile);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << pipesFile << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        vector<string> tokens = splitString(line, ',');
        if(tokens.size() == 4){
            string source = tokens[0];
            string target = tokens[1];
            int capacity = stoi(tokens[2]);
            int direction = stoi(tokens[3]);

            char typeChar = source[0];
            node_type sourceType;
            if (typeChar == 'R') {
                sourceType = node_type::reservoir;
            } else if (typeChar == 'C') {
                sourceType = node_type::city;
            } else if (typeChar == 'P') {
                sourceType = node_type::station;
            } else {
                cerr << "Error: Invalid node type for source " << source << endl;
                continue;
            }

            typeChar = target[0];
            node_type targetType;
            if (typeChar == 'R') {
                targetType = node_type::reservoir;
            } else if (typeChar == 'C') {
                targetType = node_type::city;
            } else if (typeChar == 'P') {
                targetType = node_type::station;
            } else {
                cerr << "Error: Invalid node type for target " << target << endl;
                continue;
            }

            Node sourceNode{sourceType, source};
            Node targetNode{targetType, target};

            PipesGraph.addVertex(sourceNode);
            PipesGraph.addVertex(targetNode);

            if (direction == 1) {
                PipesGraph.addEdge(sourceNode, targetNode, capacity, direction);
            } else if (direction == 0) {
                PipesGraph.addBidirectionalEdge(sourceNode, targetNode, capacity, direction);
            } else {
                cerr << "Error: Invalid direction value for edge from " << source << " to " << target << endl;
                continue;
            }
        }
    }
    file.close();
}

const unordered_map<string, Reservoir>* DataReader::getReservoirsMap() const {
    return &reservoirsMap;
}

const unordered_map<string, Station>* DataReader::getStationsMap() const {
    return &stationsMap;
}

const unordered_map<string, City>* DataReader::getCitiesMap() const {
    return &citiesMap;
}

const Graph<Node>* DataReader::getPipesGraph() const {
    return &PipesGraph;
}


void DataReader::loadData() {
    loadReservoirs("../Project1DataSetSmall/Reservoirs_Madeira.csv");
    loadStations("../Project1DataSetSmall/Stations_Madeira.csv");
    loadCities("../Project1DataSetSmall/Cities_Madeira.csv");
    loadPipes("../Project1DataSetSmall/Pipes_Madeira.csv");
}