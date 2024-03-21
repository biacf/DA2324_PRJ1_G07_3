//
// Created by AnaBeatrizCarneiroFe on 21/03/2024.
//

#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>

class Pipe;
class Node;
class WaterNetwork;

enum node_type{
    water_res,
    station,
    city
};

class Node{
private:
    node_type nt;
    std::string ID;
    std::string code;
    std::string name;
    std::string municipality;
    int max_delivery;
    int demand;
    int population;
    std::vector<Pipe*> conn_pipes;
public:
};

class Pipe{
private:
    Node* source;
    Node* destination;
    int capacity;
public:
};

class WaterNetwork {
private:
    std::vector<Node*> nodes;
public:
    std::vector<Node*> getNodes(){return nodes;};
};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
