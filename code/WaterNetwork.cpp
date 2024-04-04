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

