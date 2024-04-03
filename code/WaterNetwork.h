//
// Created by AnaBeatrizCarneiroFe on 21/03/2024.
//

#ifndef DA2324_PRJ1_G07_3_WATERNETWORK_H
#define DA2324_PRJ1_G07_3_WATERNETWORK_H

#include <string>
#include <vector>
#include "DataReader.h"



class WaterNetwork {
public:
    WaterNetwork();


private:
    void initializeData();
    DataReader dataReader;
};


#endif //DA2324_PRJ1_G07_3_WATERNETWORK_H
