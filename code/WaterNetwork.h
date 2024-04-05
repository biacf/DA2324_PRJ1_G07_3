#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>
#include "DataReader.h"



class WaterNetwork {
public:
    WaterNetwork();


    void  removeWaterReservoir(unordered_map<string, int> mflow);
    void use_maxFlow();
    unordered_map<string, int> calculateMaxFlow(const Graph<Node>& pipesGraph);
    int bfsMaxFlow(const Graph<Node>& graph, Vertex<Node>* source, Vertex<Node>* sink, unordered_map<string, int>& maxFlow);
    unordered_map<string, int> edmondsKarpMaxFlow(const Graph<Node>& graph, const vector<Node>& sources, const vector<Node>& sinks, const unordered_map<string, Station>& stationsMap);

    DataReader dataReader;
private:
    void initializeData();

};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
