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
