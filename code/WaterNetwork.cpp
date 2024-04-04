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


void WaterNetwork::removeWaterReservoir(unordered_map<string, int> mflow) {
    std::string wr_code;
    Graph<Node> copy = *dataReader.getPipesGraph();
    std::vector<std::string> removed_reservoirs;
    bool breaking = true;

    while(breaking){
        bool found = false;
        while(true){
            std::cout << "Select Water Reservoir: ";
            std::cin >> wr_code;
            std::cout << std::endl;

            for(const auto& w: removed_reservoirs){
                if(w == wr_code){
                    std::cout << "Reservoir already removed!" << std::endl;
                    found = true;
                }
            }

            if(!found){
                if(getDataReader()->getReservoirsMap()->find(wr_code) == getDataReader()->getReservoirsMap()->end()){
                    std::cout << "Invalid Water Reservoir code" << std::endl;
                    found = true;
                }
                else{
                    Node node;
                    node.code = wr_code;
                    node.type = reservoir;
                    std::cout << "We out here!" << std::endl;
                    if(copy.removeVertex(node)){
                        removed_reservoirs.push_back(wr_code);
                        std::cout << "Node was pushed back!" << std::endl;
                    }
                }
            }
            break;
        }
        if(!found){
            int demand;
            std::vector<string> aff_cities;
            unordered_map<string, int> updated = calculateMaxFlow(); //mudar quando novo maxflow

            for(const auto& c:updated){
                demand = dataReader.getCitiesMap()->find(c.first)->second.demand;
                if(c.second < demand){
                    aff_cities.push_back(dataReader.getCitiesMap()->find(c.first)->second.name);
                }
            }

            if(aff_cities.empty()){
                std::cout << "No cities were affected by the removal of " << wr_code << std::endl;
            }
            else{
                std::cout << "Affected cities: " << std::endl;
                for(auto c: aff_cities){
                    std::cout << c << std::endl;
                }
            }
        }
        int option;
        std::cout << "Do you want to remove more reservoirs?(0/1) ";
        std::cin >> option;
        if(!option){
            breaking = false;
        }

    }



}


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
    for (const auto& reservoirEntry : *reservoirsMap) {
        sources.push_back(Node{node_type::reservoir, reservoirEntry.second.code});
    }
    for (const auto& cityEntry : *citiesMap) {
        sinks.push_back(Node{node_type::city, cityEntry.second.code});
    }

    // Calculate max flow using Edmonds-Karp algorithm
    unordered_map<string, int> maxFlow = edmondsKarpMaxFlow((Graph<Node> &) pipesGraph, sources, sinks, *stationsMap);

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
            int flow = bfsMaxFlow(graph, sourceVertex, sinkVertex, (unordered_map<std::string, int> &) stationsMap);
            // Update max flow for the sink city
            maxFlow[sink.code] += flow;
        }
    }
    return maxFlow;
}

