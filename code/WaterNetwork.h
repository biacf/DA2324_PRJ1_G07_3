//
// Created by AnaBeatrizCarneiroFe on 21/03/2024.
//

#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>
#include "DataReader.h"



class WaterNetwork {
public:
    WaterNetwork();
    unordered_map<string, int> calculateMaxFlow(const Graph<Node>& pipesGraph);
    double bfsMaxFlow(const Graph<Node>& graph, Vertex<Node>* source, Vertex<Node>* sink, unordered_map<string, int>& maxFlow);
    unordered_map<string, int> edmondsKarpMaxFlow(const Graph<Node>& graph, const vector<Node>& sources, const vector<Node>& sinks, const unordered_map<string, Station>& stationsMap);


    void initializeData();

    DataReader dataReader;
};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
