#include <map>
#include "WaterNetwork.h"

WaterNetwork::WaterNetwork() {
    initializeData();
}

void WaterNetwork::initializeData(){
    dataReader.loadData();
}

/// \brief Computes the maximum flow for cities from reservoirs using the Edmonds-Karp algorithm.
/// \param reservoirs A vector of reservoir nodes.
/// \param cities A vector of city nodes.
/// \param pipes The graph representing the water network.
/// \return An unordered map containing the maximum flow for each city.
/// \note Time Complexity: O(R * C * E), where R is the number of reservoirs, C is the number of cities, and E is the number of edges.
unordered_map<string, int> WaterNetwork::edmondsKarpMaxFlow(vector<Node> reservoirs, vector<Node> cities, Graph<Node> pipes) {
    resetFlow(&pipes);
    unordered_map<string,int> cities_max_flow;
    for(const auto& city : cities){
        Vertex<Node>* sink = pipes.findVertex(city);
        if(sink == nullptr){
            std::cout << "Error retrieving city node" << std::endl;
            return cities_max_flow;
        }
        int totalMaxFlow = 0;

        for(const Node& res : reservoirs){
            Vertex<Node>* source = pipes.findVertex(res);
            if(source == nullptr){
                std::cout << "Error retrieving reservoir node" << std::endl;
                continue;
            }
            int maxFlow = BFSMaxFlow(source, sink);
            totalMaxFlow += maxFlow;
        }
        int actualFlow = min(totalMaxFlow, dataReader.getCitiesMap()->find(city.code)->second.demand);
        cities_max_flow.insert({city.code, actualFlow});
    }

    return cities_max_flow;
}

/// \brief Computes the maximum flow from a source to a sink using BFS in the residual graph.
/// \param source The source vertex.
/// \param sink The sink vertex.
/// \return The maximum flow from source to sink.
/// \note Time Complexity: O(E * V^2), where E is the number of edges and V is the number of vertices.
int WaterNetwork::BFSMaxFlow(Vertex<Node> *source, Vertex<Node> *sink) {
    int maxFlow = 0;
    unordered_map<Vertex<Node>*, Edge<Node>*> parent;

    queue<Vertex<Node>*> q;
    q.push(source);

    unordered_set<Vertex<Node>*> visited;
    visited.insert(source);

    while (!q.empty()) {
        Vertex<Node>* u = q.front();
        q.pop();

        for (Edge<Node>* edge : u->getAdj()) {
            Vertex<Node>* v = edge->getDest();
            if (visited.count(v) == 0 && (edge->getCapacity() - edge->getFlow() )> 0) {
                visited.insert(v);
                parent[v] = edge;
                q.push(v);
                if (v == sink) {
                    Vertex<Node>* current = sink;
                    int minCapacity = INT_MAX;

                    while (current != source) {
                        Edge<Node>* parentEdge = parent[current];
                        minCapacity = min(minCapacity, (int) (parentEdge->getCapacity() - parentEdge->getFlow()));
                        current = parentEdge->getOrig();
                    }

                    current = sink;
                    while (current != source) {
                        Edge<Node>* parentEdge = parent[current];
                        parentEdge->setFlow(parentEdge->getFlow() + minCapacity);
                        if(parentEdge->getReverse() != nullptr){
                            parentEdge->getReverse()->setFlow(parentEdge->getReverse()->getFlow() - minCapacity);
                        }
                        current = parentEdge->getOrig();
                    }

                    maxFlow += minCapacity;
                    parent.clear();
                    break;
                }
            }
        }
    }

    return maxFlow;
}

void WaterNetwork::resetFlow(Graph<Node> *graph) {
    for(auto v: graph->getVertexSet()){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
}

/// \brief Removes a water reservoir from the network and evaluates its impact on city flows.
///
/// \param reservoirs Vector of remaining reservoir nodes in the network.
/// \param cities Vector of city nodes in the network.
/// \param mflow Mapping of city codes to their respective flow demands.
///
/// \return Updated city flow capacities after reservoir removal.
///
/// \note Time Complexity: O(R * (V + E)), where R is the number of reservoirs, V is the number of nodes (cities, stations), and E is the number of edges (pipes).
void WaterNetwork::removeWaterReservoir(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int>& mflow) {
    Graph<Node> copy = dataReader.getPipesGraph();

    while (true) {
        std::string wr_code;
        std::cout << "Select Water Reservoir to Remove (or enter 'done' to finish): ";
        std::cin >> wr_code;
        std::cout << std::endl;

        if (wr_code == "done") {
            break;
        }

        auto it = std::find_if(reservoirs.begin(), reservoirs.end(),[&wr_code](const Node& n) { return n.code == wr_code; });

        if (it != reservoirs.end()) {
            Node reservoir = *it;

            if (copy.removeVertex(reservoir)) {
                std::cout << "Removed reservoir: " << reservoir.code << std::endl;

                reservoirs.erase(it);

                unordered_map<string, int> updated = edmondsKarpMaxFlow(reservoirs, cities, copy);

                vector<string> aff_cities;
                for (const auto& c : updated) {
                    if (c.second < mflow.find(c.first)->second) {
                        aff_cities.push_back(c.first);
                    }
                }

                if (aff_cities.empty()) {
                    std::cout << "No cities were affected by the removal of " << reservoir.code << std::endl;
                } else {
                    std::cout << "Affected cities: " << std::endl;
                    for (const auto& c : aff_cities) {
                        std::cout << "CITY: " << dataReader.getCitiesMap()->find(c)->second.name <<" | OLD FLOW: " << mflow.find(c)->second << " | NEW FLOW: " << updated.find(c)->second << std::endl;
                    }
                }
            } else {
                std::cout << "Failed to remove reservoir: " << reservoir.code << std::endl;
            }
        } else {
            std::cout << "Invalid Water Reservoir code" << std::endl;
        }
    }
}

/// \brief Removes a pumping station from the network and evaluates its impact on city flows.
///
/// \param reservoirs Vector of remaining reservoir nodes in the network.
/// \param cities Vector of city nodes in the network.
/// \param mflow Mapping of city codes to their respective flow demands.
///
/// \return Updated city flow capacities after station removal.
///
/// \note Time Complexity: O(S * (V + E)), where S is the number of pumping stations, V is the number of nodes (cities, reservoirs), and E is the number of edges (pipes).
void WaterNetwork::removePumpingStations(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int>& mflow) {
    unordered_map<string, Station> stations = *dataReader.getStationsMap();
    unordered_map<string, int> currentFlow;



    std::string stationCode;
    std::cout << "Select Pumping Station to Remove: ";
    std::cin >> stationCode;
    std::cout << std::endl;

    auto it = stations.find(stationCode);
    if (it != stations.end()) {
        Station station_ = it->second;

        Node stationNode;
        stationNode.type = station;
        stationNode.code = stationCode;

        Graph<Node> copy = dataReader.getPipesGraph();
        if (copy.removeVertex(stationNode)) {
            std::cout << "Removed pumping station: " << stationCode << std::endl;

            stations.erase(it);

            currentFlow = edmondsKarpMaxFlow(reservoirs, cities, copy);


            std::cout << "Affected cities if Pumping Station " << stationCode << " is removed: " << std::endl;
            bool allCitiesUnaffected = true;
            for (const auto& cityFlow : currentFlow) {
                const string& cityName = cityFlow.first;
                int flow = cityFlow.second;
                int demand = mflow.at(cityName);

                if (flow < demand) {
                    std::cout << "CITY: " << dataReader.getCitiesMap()->find(cityName)->second.name << " | CODE: " << cityName << " | OLD FLOW: " << demand << " | NEW FLOW: " << flow << std::endl;
                    allCitiesUnaffected = false;
                }
            }

            if (allCitiesUnaffected) {
                std::cout << "No affected cities!" << std::endl;
            }
            } else {
            std::cout << "Failed to remove pumping station: " << stationCode << std::endl;
            }
        } else {
            std::cout << "Invalid Pumping Station code" << std::endl;
        }

}

/// \brief Removes a pipeline between specified nodes and evaluates its impact on city flows.
///
/// \param reservoirs Vector of remaining reservoir nodes in the network.
/// \param cities Vector of city nodes in the network.
/// \param mflow Mapping of city codes to their respective flow demands.
///
/// \return Updated city flow capacities after pipeline removal.
///
/// \note Time Complexity: O(V + E), where V is the number of nodes (cities, reservoirs, stations) and E is the number of edges (pipes).
void WaterNetwork::removePipeline(vector<Node> reservoirs, vector<Node> cities, const unordered_map<string, int> &mflow) {
    std::string source_code;
    std::string dest_code;
    int option;
    Node source;
    Node destination;

    std::cout << "Source is: " << std::endl;
    std::cout << "1. Water Reservoir" << std::endl;
    std::cout << "2. Pumping Station" << std::endl;
    std::cout << "3. City" << std::endl;
    std::cout << "Option: ";
    std::cin >> option;
    while(true){
        if(option < 1 || option > 3){
            std::cout << "Valid Option: ";
            std::cin >> option;
        }
        else{
            break;
        }
    }
    std::cout << "Source code: ";
    std::cin >> source_code;
    while(true) {
        bool found = false;
        if (option == 1) {
            if (dataReader.getReservoirsMap()->find(source_code) == dataReader.getReservoirsMap()->end()) {
                found = false;
            }
            else{
                found = true;
                source.type = reservoir;
            }
        }
        else if(option == 2){
            if (dataReader.getStationsMap()->find(source_code) == dataReader.getStationsMap()->end()) {
                found = false;
            }
            else{
                found = true;
                source.type = station;
            }
        }
        else if(option == 3){
            if (dataReader.getCitiesMap()->find(source_code) == dataReader.getCitiesMap()->end()) {
                found = false;
            }
            else{
                found = true;
                source.type = city;
            }
        }
        else{
            return;
        }

        if(found){
            source.code = source_code;
            break;
        }
        else{
            std::cout << "Valid source code: ";
            std::cin >> source_code;
        }
    }


    std::cout << "Destination is: " << std::endl;
    std::cout << "1. Water Reservoir" << std::endl;
    std::cout << "2. Pumping Station" << std::endl;
    std::cout << "3. City" << std::endl;
    std::cout << "Option: ";
    std::cin >> option;
    while(true){
        if(option < 1 || option > 3){
            std::cout << "Valid Option: ";
            std::cin >> option;
        }
        else{break;}
    }
    std::cout << "Destination code: ";
    std::cin >> dest_code;
    while(true) {
        bool found = false;
        if (option == 1) {
            if (dataReader.getReservoirsMap()->find(dest_code) == dataReader.getReservoirsMap()->end()) {
                found = false;
            }
            else{
                found = true;
                destination.type = reservoir;
            }
        }
        else if(option == 2){
            if (dataReader.getStationsMap()->find(dest_code) == dataReader.getStationsMap()->end()) {
                found = false;
            }
            else{
                found = true;
                destination.type = station;
            }
        }
        else if(option == 3){
            if (dataReader.getCitiesMap()->find(dest_code) == dataReader.getCitiesMap()->end()) {
                found = false;
            }
            else{
                found = true;
                destination.type = city;
            }
        }
        else{
            return;
        }

        if(found){
            destination.code = dest_code;
            break;
        }
        else{
            std::cout << "Valid destination code: ";
            std::cin >> dest_code;
        }
    }

    bool found = false;
    Graph<Node> copy = dataReader.getPipesGraph();

    if(copy.findVertex(source) == nullptr){
        std::cout << "Invalid Source" << std::endl;
        return;
    }
    else{
        if(copy.findVertex(destination)== nullptr){
            std::cout << "Invalid destination" << std::endl;
            return;
        }

        for(auto e : copy.findVertex(source)->getAdj()){
            if(e->getDest()->getInfo() == destination){
                found = true;
            }
        }

        if(found){
            copy.removeEdge(source, destination);
            std::unordered_map<string, int> updated = edmondsKarpMaxFlow(reservoirs, cities, copy);
            std::cout << "Affected cities: " << std:: endl;
            for(auto a : updated){
                if(a.second < mflow.find(a.first)->second){
                    std::cout << "CITY: " << dataReader.getCitiesMap()->find(a.first)->second.name << "| CODE: " << a.first << " | OLD FLOW: " << mflow.find(a.first)->second << " | NEW FLOW: " << a.second << std::endl;
                }
            }
        }
        else{
            std::cout << "Edge doesn't exist";
        }
    }
}

///\brief Prompts the user for the desired city to analyze
void WaterNetwork::vitalPipelines() {
    string city_code;

    while (true) {
        std::cout << "Insert valid city code: ";
        std::cin >> city_code;
        if (dataReader.getCitiesMap()->find(city_code) == dataReader.getCitiesMap()->end()) {
            std::cout << "Invalid city code!" << std::endl;
        } else {
            break;
        }
    }

    minCut(city_code);
}

/// \brief Performs a Breadth-First Search (BFS) to find all reachable nodes from a given source city.
/// \param visited Reference to an unordered_set containing visited city codes.
/// @param source The starting city code for the BFS traversal.
/// \note Time Complexity: O(V + E), where V is the number of vertices (cities) and E is the number of edges (pipes).
void WaterNetwork::minCutBFS(unordered_set<string>& visited, const string& source) {
    queue<string> q;
    q.push(source);
    visited.insert(source);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        // Find the vertex corresponding to the current city code
        Node cityNode;
        cityNode.type = city;
        cityNode.code = current;
        Vertex<Node>* currentVertex = dataReader.getPipesGraph().findVertex(cityNode);

        if (currentVertex) {
            // Traverse adjacent edges
            for (Edge<Node>* edge : currentVertex->getAdj()) {
                if (edge && (edge->getCapacity() - edge->getFlow() > 0) && visited.find(edge->getDest()->getInfo().code) == visited.end()) {
                    q.push(edge->getDest()->getInfo().code);
                    visited.insert(edge->getDest()->getInfo().code);
                }
            }
        }
    }
}

/// \brief Computes the minimum cut in the network for a specified city.
/// \param c_code The city code for which the minimum cut is calculated.
/// This function identifies all pipes (edges) that, if cut, would disconnect the specified city from the source.
/// \note Time Complexity: O(V + E), where V is the number of vertices (cities) and E is the number of edges (pipes).
void WaterNetwork::minCut(const string& c_code) {
    std::unordered_set<string> visited;
    minCutBFS(visited, c_code);

    // Find the source city vertex
    Node sourceCityNode;
    sourceCityNode.type = city;
    sourceCityNode.code = c_code;
    Vertex<Node>* sourceVertex = dataReader.getPipesGraph().findVertex(sourceCityNode);

    if (!sourceVertex) {
        std::cout << "Error: Source city vertex not found." << std::endl;
        return;
    }

    vector<Edge<Node>*> minCutEdges;
    // Iterate over the adjacency list of the source city vertex
    for (Edge<Node>* edge : sourceVertex->getAdj()) {
        if (edge && visited.find(edge->getDest()->getInfo().code) != visited.end()) {
            minCutEdges.push_back(edge);
        }
    }

    if (minCutEdges.empty()) {
        std::cout << "No pipes would negatively affect " << dataReader.getCitiesMap()->find(c_code)->second.name << " flow if cut." << std::endl;
    } else {
        std::cout << "The following pipes would negatively affect this city's flow if cut: " << std::endl;
        for (Edge<Node>* edge : minCutEdges) {
            std::cout << "Pipe that connects " << edge->getOrig()->getInfo().code << " to " << edge->getDest()->getInfo().code << std::endl;
        }
    }
}