#include <iostream>
#include "WaterNetwork.h"



//int main() {
//>>>>>>> 24f0e91ccfa9c4f853b915348d90514089f48a77
//
//    char option;
//    WaterNetwork waterNetwork;
//    unordered_map<string, int> mflow;
//
//    std::cout << "##################################################" << std::endl;
//    std::cout << "Welcome to the L.EIC Water Supply Management Tool!" << std::endl;
//    std::cout << "##################################################" << std::endl;
//
//    //mflow = waterNetwork.calculateMaxFlow();
//
//    while(true){
//        std::cout << "\nWhat would you like to simulate today?" << std::endl;
//        std::cout << "a. Check Maximum Flow options" << std::endl;
//        std::cout << "b. Check under supplied cities" << std::endl;
//        std::cout << "c. Remove Water Reservoirs" << std::endl;
//        std::cout << "d. Remove Pumping Stations" << std::endl;
//        std::cout << "e. Vital Pipelines" << std::endl;
//        std::cout << "f. Remove pipelines" << std::endl;
//        std::cout << "g. Exit" << std::endl;
//
//        std::cout << "\nOption: ";
//        std::cin >> option;
//        while(option < 'a' || option > 'g'){
//            std::cout << "Please enter a valid option." << std::endl;
//            std::cout << "\nOption: ";
//            std::cin >> option;
//        }
//
//        switch(option){
//            case 'a':{
//                break;
//            }
//            case 'b':{
//                break;
//            }
//            case 'c':{
//                waterNetwork.removeWaterReservoir(mflow);
//                break;
//            }
//            case 'd':{
//                break;
//            }
//            case 'e':{
//                break;
//            }
//            case 'f':{
//                break;
//            }
//            case 'g':{
//                return 0;
//            }
//            default:{
//                return 0;
//            }
//        }
//    }
//    return 0;
//}

int main(){
    WaterNetwork waterNetwork;
    waterNetwork.dataReader.loadData();
    waterNetwork.use_maxFlow();
    return 0;
}
