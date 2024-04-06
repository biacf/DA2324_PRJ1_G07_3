#include <iostream>
#include "WaterNetwork.h"

int main(){
    WaterNetwork waterNetwork;
    vector<Node> cities;
    vector<Node> reservoirs;
    for(auto c: *waterNetwork.dataReader.getCitiesMap()){
        cities.push_back(Node{city,c.first});
    }

    for(auto r : *waterNetwork.dataReader.getReservoirsMap()){
        reservoirs.push_back(Node{reservoir,r.first});
    }

    unordered_map<string, int> mflow = waterNetwork.edmondsKarpMaxFlow(reservoirs, cities,waterNetwork.dataReader.getPipesGraph());

    std::cout << "##################################################" << std::endl;
    std::cout << "Welcome to the L.EIC Water Supply Management Tool!" << std::endl;
    std::cout << "##################################################" << std::endl;
    char option;

    while(true){
        std::cout << "\nWhat would you like to simulate today?" << std::endl;
        std::cout << "a. Check Maximum Flow options" << std::endl;
        std::cout << "b. Check under supplied cities" << std::endl;
        std::cout << "c. Remove Water Reservoirs" << std::endl;
        std::cout << "d. Remove Pumping Stations" << std::endl;
        std::cout << "e. Vital Pipelines" << std::endl;
        std::cout << "f. Remove pipelines" << std::endl;
        std::cout << "g. Exit" << std::endl;

        std::cout << "\nOption: ";
        std::cin >> option;
        while(option < 'a' || option > 'g'){
            std::cout << "Please enter a valid option." << std::endl;
            std::cout << "\nOption: ";
            std::cin >> option;
        }

        switch(option){
            case 'a':{
                unordered_map<string, int> maxFlow;
                vector<Node> cities;
                vector<Node> reservoirs;
                Node city_;
                city_.type = city;
                Node reservoir_;
                reservoir_.type = reservoir;
                int totalMaxFlow = 0;

                std::cout << "Select one of the following Maximum Flow options: " << std::endl;
                std::cout << "1. Max Flow for every city" << std::endl;
                std::cout << "2. Max Flow for a specific city" << std::endl;
                std::cout << "Option: ";
                std::cin >> option;

                while(option < '1' || option > '2'){
                    std::cout << "Please enter a valid option." << std::endl;
                    std::cout << "\nOption: ";
                    std::cin >> option;
                }

                if(option == '1'){
                    for(const auto& c : *waterNetwork.dataReader.getCitiesMap()){
                        city_.code = c.first;
                        cities.push_back(city_);
                    }
                }
                else if(option == '2'){
                    string city_code;
                    std::cout << "Insert city code: ";
                    std::cin >> city_code;
                    while(true){
                        if(waterNetwork.dataReader.getCitiesMap()->find(city_code) == waterNetwork.dataReader.getCitiesMap()->end()){
                            std::cout << "Insert valid city code: ";
                            std::cin >> city_code;
                        }
                        else{
                            break;
                        }
                    }
                    city_.code = city_code;
                    cities.push_back(city_);
                }
                else{
                    std::cout << "Error: invalid option";
                    break;
                }
                for(const auto& r : *waterNetwork.dataReader.getReservoirsMap()){
                    reservoir_.code = r.first;
                    reservoirs.push_back(reservoir_);
                }

                maxFlow = waterNetwork.edmondsKarpMaxFlow(reservoirs, cities,waterNetwork.dataReader.getPipesGraph());

                std::cout << "Cities and Maximum Flow: " << std::endl;
                for(const auto& a : maxFlow){
                    City current = waterNetwork.dataReader.getCitiesMap()->find(a.first)->second;
                    std::cout << "City: " << current.name << " | Code: " << current.code << " | Max. Flow: " << a.second << std::endl;
                    totalMaxFlow += a.second;
                }
                std::cout << "Total Max Flow: " << totalMaxFlow << std::endl;
                break;
            }
            case 'b':{
                std::cout << "Under supplied cities: " << std::endl;

                unordered_map<string, int> maxFlow;
                vector<Node> cities;
                vector<Node> reservoirs;
                Node city_;
                city_.type = city;
                Node reservoir_;
                reservoir_.type = reservoir;

                for(const auto& c : *waterNetwork.dataReader.getCitiesMap()){
                    city_.code = c.first;
                    cities.push_back(city_);
                }

                for(const auto& r : *waterNetwork.dataReader.getReservoirsMap()){
                    reservoir_.code = r.first;
                    reservoirs.push_back(reservoir_);
                }

                maxFlow = waterNetwork.edmondsKarpMaxFlow(reservoirs, cities,waterNetwork.dataReader.getPipesGraph());

                for(const auto& a : maxFlow){
                    City current = waterNetwork.dataReader.getCitiesMap()->find(a.first)->second;
                    if(current.demand > a.second){
                        std::cout << "CITY: " << current.name << " | CODE: " << current.code << " | DEFICIT: " << current.demand - a.second << std::endl;
                    }
                }

                break;
            }
            case 'c':{
                waterNetwork.removeWaterReservoir(reservoirs, cities, mflow);
                break;
            }
            case 'd':{
                waterNetwork.removePumpingStations(reservoirs, cities, mflow);
                break;
            }
            case 'e':{
                waterNetwork.vitalPipelines();
                break;
            }
            case 'f':{
                waterNetwork.removePipeline(reservoirs, cities, mflow);
                break;
            }
            case 'g':{
                return 0;
            }
            default:{
                return 0;
            }
        }
    }
    return 0;
}