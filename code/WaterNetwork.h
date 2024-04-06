#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>
#include <unordered_set>
#include "DataReader.h"


/// \class WaterNetwork
/// \brief Class used to perform various operations in order to analyze a water network
class WaterNetwork {
public:
    /// \brief Default constructor for WaterNetwork.
    WaterNetwork();

    void  removeWaterReservoir(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int>& mflow);
    unordered_map<string, int> edmondsKarpMaxFlow(vector<Node> reservoirs, vector<Node> cities, Graph<Node> pipes);
    void removePumpingStations(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int>& mflow);
    void removePipeline(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int>& mflow);
    void vitalPipelines();
    void minCut(const string& c_code);
    void minCutBFS(std::unordered_set<string>& visited, const string& source);
    DataReader dataReader;
private:

    int BFSMaxFlow(Vertex<Node>* source, Vertex<Node>* sink);
    /// \brief Resets the flow of all edges in the graph to zero.
    /// \param graph The graph to reset.
    void resetFlow(Graph<Node> * graph);
    /// \brief Initializes the water network by loading data.
    void initializeData();

};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
