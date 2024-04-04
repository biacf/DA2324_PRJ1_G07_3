//
// Created by AnaBeatrizCarneiroFe on 21/03/2024.
//

#include "WaterNetwork.h"

WaterNetwork::WaterNetwork() {
    initializeData();
}

void WaterNetwork::initializeData(){
    dataReader.loadData();
}

<<<<<<< HEAD
void WaterNetwork::removeWaterReservoir() {
    std::string wr_code;
    std::vector<std::string> removed_reservoirs;

    while(true){
        std::cout << "Select Water Reservoir: ";
        std::cin >> wr_code;
        std::cout << std::endl;

        if(getDataReader()->getReservoirsMap()->find(wr_code) == getDataReader()->getReservoirsMap()->end()){
            std::cout << "Invalid Water Reservoir code" << std::endl;
        }
        break;
    }



    //criar clone de grafo, tirar wr, query se quer mais e tirar do  clone e ir listando as affected cities


    //calculate flow
    //use edmonds karp
    //remove
    //compare new flow to og flow
    //have to recalculate with edmonds karp

}

=======
unordered_map<string, int> WaterNetwork::calculateMaxFlow() {
    unordered_map<string, int> maxFlows;

    // Get the graph representing the water network
    const Graph<Node>* pipesGraph = dataReader.getPipesGraph();

    // Retrieve reservoirs, cities, and stations maps
    const unordered_map<string, Reservoir>* reservoirsMap = dataReader.getReservoirsMap();
    const unordered_map<string, City>* citiesMap = dataReader.getCitiesMap();
    const unordered_map<string, Station>* stationsMap = dataReader.getStationsMap();

    // Convert sources and sinks to vectors
    vector<Node> sources;
    vector<Node> sinks;
    for (const auto& reservoirEntry : reservoirsMap) {
        sources.push_back(Node{node_type::reservoir, reservoirEntry.second.code});
    }
    for (const auto& cityEntry : citiesMap) {
        sinks.push_back(Node{node_type::city, cityEntry.second.code});
    }

    // Calculate max flow using Edmonds-Karp algorithm
    unordered_map<string, int> maxFlow = edmondsKarpMaxFlow(pipesGraph, sources, sinks, stationsMap);

    return maxFlow;
}

double WaterNetwork::bfsMaxFlow(Graph<Node>& graph, Vertex<Node>* source, Vertex<Node>* sink, unordered_map<string, int>& maxFlow) {
    std::unordered_map<Vertex<Node>*, double> flow; // Stores flow through each edge
    std::unordered_map<Vertex<Node>*, Edge<Node>*> parent; // Stores parent edge for each vertex
    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            flow[e->getDest()] = 0;
        }
    }

    std::queue<Vertex<Node>*> q;
    q.push(source);
    parent[source] = nullptr;
    flow[source] = std::numeric_limits<double>::infinity();

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto e : u->getAdj()) {
            auto v = e->getDest();
            if (flow[v] == 0 && e->getCapacity() > 0) {
                parent[v] = e;
                flow[v] = std::min(flow[u], static_cast<double>(e->getCapacity()));
                if (v != sink) {
                    q.push(v);
                } else {
                    // Found augmenting path
                    auto pathFlow = flow[sink];
                    auto curr = sink;
                    while (parent[curr] != nullptr) {
                        auto edge = parent[curr];
                        edge->setFlow(edge->getFlow() + pathFlow);
                        auto reverseEdge = edge->getReverse();
                        reverseEdge->setFlow(reverseEdge->getFlow() - pathFlow);
                        curr = edge->getOrig();
                    }
                    return pathFlow;
                }
            }
        }
    }
    return 0; // No augmenting path found
}

unordered_map<string, int> WaterNetwork::edmondsKarpMaxFlow(Graph<Node>& graph, const vector<Node>& sources, const vector<Node>& sinks, const unordered_map<string, Station>& stationsMap) {
    unordered_map<string, int> maxFlow; // Map to store max flow for each city

    // Initialize max flow for each city
    for (const auto& city : sinks) {
        maxFlow[city.code] = 0;
    }

    // Iterate over each source
    for (const auto& source : sources) {
        Vertex<Node>* sourceVertex = graph.findVertex(source);
        // Iterate over each sink
        for (const auto& sink : sinks) {
            Vertex<Node>* sinkVertex = graph.findVertex(sink);
            // Compute max flow from source to sink using BFS
            int flow = bfsMaxFlow(graph, sourceVertex, sinkVertex, stationsMap);
            // Update max flow for the sink city
            maxFlow[sink.code] += flow;
        }
    }
    return maxFlow;
}
>>>>>>> e055835c475e0333c2ef66c560040c9d87b3489f
