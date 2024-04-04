#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>
#include "DataReader.h"



class WaterNetwork {
public:
    WaterNetwork();

    void  removeWaterReservoir(unordered_map<string, int> mflow);
    DataReader* getDataReader(){return &dataReader;};

    unordered_map<string, int> calculateMaxFlow();
    double bfsMaxFlow(Graph<Node>& graph, Vertex<Node>* source, Vertex<Node>* sink, unordered_map<string, int>& maxFlow);
    unordered_map<string, int> edmondsKarpMaxFlow(Graph<Node>& graph, const vector<Node>& sources, const vector<Node>& sinks, const unordered_map<string, Station>& stationsMap);

private:
    void initializeData();
    DataReader dataReader; 
};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
