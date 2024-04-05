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

//unordered_map<string, int> WaterNetwork::calculateMaxFlow(const Graph<Node>& pipesGraph) {
//    unordered_map<string, int> maxFlows;
//
//    // Retrieve reservoirs, cities, and stations maps
//    const unordered_map<string, Reservoir>* reservoirsMap = dataReader.getReservoirsMap();
//    const unordered_map<string, City>* citiesMap = dataReader.getCitiesMap();
//    const unordered_map<string, Station>* stationsMap = dataReader.getStationsMap();
//
//    // Convert sources and sinks to vectors
//    vector<Node> sources;
//    vector<Node> sinks;
//    for (const auto& reservoirEntry : *reservoirsMap) {
//        sources.push_back(Node{node_type::reservoir, reservoirEntry.second.code});
//    }
//    for (const auto& cityEntry : *citiesMap) {
//        sinks.push_back(Node{node_type::city, cityEntry.second.code});
//    }
//
//    // Calculate max flow using Edmonds-Karp algorithm
//    unordered_map<string, int> maxFlow = edmondsKarpMaxFlow(pipesGraph, sources, sinks, *stationsMap);
//
//    return maxFlow;
//}
//
//double WaterNetwork::bfsMaxFlow(const Graph<Node>& graph, Vertex<Node>* source, Vertex<Node>* sink, unordered_map<string, int>& maxFlow) {
//    std::unordered_map<Vertex<Node>*, double> flow; // Stores flow through each edge
//    std::unordered_map<Vertex<Node>*, Edge<Node>*> parent; // Stores parent edge for each vertex
//    for (auto v : graph.getVertexSet()) {
//        for (auto e : v->getAdj()) {
//            flow[(*e).getDest()] = 0;
//        }
//    }
//
//    std::queue<Vertex<Node>*> q;
//    q.push(source);
//    parent[source] = nullptr;
//    flow[source] = std::numeric_limits<double>::infinity();
//
//    while (!q.empty()) {
//        auto u = q.front();
//        q.pop();
//        for (auto e : u->getAdj()) {
//            auto v = (*e).getDest();
//            if (flow[v] == 0 && e->getCapacity() > 0) {
//                parent[v] = e;
//                flow[v] = std::min(flow[u], static_cast<double>(e->getCapacity()));
//                if (v != sink) {
//                    q.push(v);
//                } else {
//                    // Found augmenting path
//                    auto pathFlow = flow[sink];
//                    auto curr = sink;
//                    while (parent[curr] != nullptr) {
//                        auto edge = parent[curr];
//                        edge->setFlow(edge->getFlow() + pathFlow);
//                        auto reverseEdge = edge->getReverse();
//                        reverseEdge->setFlow(reverseEdge->getFlow() - pathFlow);
//                        curr = edge->getOrig();
//                    }
//                    return pathFlow;
//                }
//            }
//        }
//    }
//    return 0; // No augmenting path found
//}
//
//unordered_map<string, int> WaterNetwork::edmondsKarpMaxFlow(const Graph<Node>& graph, const vector<Node>& sources, const vector<Node>& sinks, const unordered_map<string, Station>& stationsMap) {
//    unordered_map<string, int> maxFlow; // Map to store max flow for each city
//
//    // Initialize max flow for each city
//    for (const auto& city : sinks) {
//        maxFlow[city.code] = 0;
//    }
//
//    // Iterate over each source
//    for (const auto& source : sources) {
//        Vertex<Node>* sourceVertex = graph.findVertex(source);
//        // Iterate over each sink
//        for (const auto& sink : sinks) {
//            Vertex<Node>* sinkVertex = graph.findVertex(sink);
//            // Compute max flow from source to sink using BFS
//            int flow = bfsMaxFlow(graph, sourceVertex, sinkVertex, maxFlow);
//            // Update max flow for the sink city
//            maxFlow[sink.code] += flow;
//        }
//    }
//    return maxFlow;
//}
