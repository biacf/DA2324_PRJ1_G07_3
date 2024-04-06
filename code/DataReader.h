#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../data_structures/Graph.h"

#ifndef DA2324_PRJ1_G07_3_DATAREADER_H
#define DA2324_PRJ1_G07_3_DATAREADER_H
/// \file DataReader.h
/// \brief Contains classes and functions for reading and loading data.

/// \enum node_type
/// \brief Represents the type of a node in the water network.
enum node_type {
    reservoir,
    station,
    city
};

/// \struct Node
/// \brief Represents a node in the water network.
struct Node {
    node_type type;  ///< The type of the node.
    string code; ///< The unique code identifying the node.

    /// \brief Overloaded equality operator for comparing nodes.
    bool operator==(const Node& other) const {
        return code == other.code;
    }

    /// \struct NodeHash
    /// \brief Computes hash for Node objects.
    struct NodeHash {
        std::size_t operator()(const Node& node) const {
            return std::hash<std::string>()(node.code);
        }
    };
};

/// \struct Reservoir
/// \brief Represents a reservoir in the water network.
struct Reservoir {
    string name; ///< The name of the reservoir.
    string municipality; ///< The municipality where the reservoir is located.
    int id; ///< The unique identifier of the reservoir.
    string code; ///< The code identifying the reservoir.
    int maxDelivery; ///< The maximum delivery capacity of the reservoir.
};

/// \struct Station
/// \brief Represents a pumping station in the water network.
struct Station {
    int id; ///< The unique identifier of the pumping station.
    string code; ///< The code identifying the pumping station.
};

/// \struct City
/// \brief Represents a city in the water network.
struct City {
    string name; ///< The name of the city.
    int id; ///< The unique identifier of the city.
    string code; ///< The code identifying the city.
    int demand; ///< The water demand of the city.
    int population; ///< The population of the city.
};

/**
 *  @struct Pipe
 *  @brief Represents a pipe connecting nodes in the water network.
 */
struct Pipe {
    Node source; ///< The source node of the pipe.
    Node destination; ///< The destination node of the pipe.
    int capacity; ///< The capacity of the pipe.
    int direction; ///< The direction of flow in the pipe (0: bidirectional, 1: unidirectional).
};

/// \class DataReader
/// \brief Class responsible for reading and loading data from CSV files.
class DataReader {
public:
    /// \brief Loads all data from CSV files into corresponding data structures.
    void loadData();
    /// \brief Splits a string into tokens based on a delimiter.
    /// \param s The input string to split.
    /// \param delimiter The character delimiter to use.
    /// \return A vector of tokens.
    vector<string> splitString(const string& s, char delimiter);
    /// \brief Loads reservoir data from a CSV file into the reservoirsMap.
    void loadReservoirs(const string& reservoirFile);
    /// \brief Loads station data from a CSV file into the stationsMap.
    void loadStations(const string& stationFile);
    /// \brief Loads city data from a CSV file into the citiesMap.
    void loadCities(const string& citiesFile);
    /// \brief Loads pipe data from a CSV file into the PipesGraph.
    void loadPipes(const string& pipesFile);
    /// \brief Retrieves a pointer to the reservoirs map.
    const unordered_map<string, Reservoir>* getReservoirsMap() const;
    /// \brief Retrieves a pointer to the stations map.
    const unordered_map<string, Station>* getStationsMap() const;
    /// \brief Retrieves a pointer to the cities map.
    const unordered_map<string, City>* getCitiesMap() const;
    /// \brief Retrieves a copy of the pipes graph.
    Graph<Node> getPipesGraph() const;

private:
    Graph<Node> PipesGraph; ///< Graph representing the network of pipes.
    unordered_map<string, Reservoir> reservoirsMap; ///< Map of reservoirs by code.
    unordered_map<string, Station> stationsMap; ///< Map of stations by code.
    unordered_map<string, City> citiesMap; ///< Map of cities by code.
};


#endif //DA2324_PRJ1_G07_3_DATAREADER_H