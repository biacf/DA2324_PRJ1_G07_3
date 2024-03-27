#include <iostream>
#include "DataReader.h"
#include "WaterNetwork.h"

//bool dealWithMissingData(WaterNetwork* wn){
//    if(wn->getNodes().empty()){
//        std::cout << "Please load data to be parsed first (option a)" << std::endl;
//        return true;
//    }
//
//    return false;
//}

int main() {

    DataReader dataReader;
    dataReader.loadReservoirs("../Project1LargeDataSet/Reservoir.csv");
    dataReader.loadPipes("../Project1LargeDataSet/Pipes.csv");

//    std::cout << "##################################################" << std::endl;
//    std::cout << "Welcome to the L.EIC Water Supply Management Tool!" << std::endl;
//    std::cout << "##################################################" << std::endl;
//
//    while(true){
//        std::cout << "\nWhat would you like to simulate today?" << std::endl;
//        std::cout << "\na. Load data to be parsed" << std::endl;
//        std::cout << "b. Check Maximum Flow options" << std::endl;
//        std::cout << "c. Check under supplied cities" << std::endl;
//        std::cout << "d. Remove Water Reservoirs" << std::endl;
//        std::cout << "e. Remove Pumping Stations" << std::endl;
//        std::cout << "f. Vital Pipelines" << std::endl;
//        std::cout << "g. Remove pipelines" << std::endl;
//        std::cout << "h. Exit" << std::endl;
//
//        std::cout << "\nOption: ";
//        std::cin >> option;
//        while(option < 'a' || option > 'h'){
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
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'c':{
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'd':{
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'e':{
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'f':{
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'g':{
//                if(dealWithMissingData(&waterNetwork)){
//                    break;
//                }
//                break;
//            }
//            case 'h':{
//                return 0;
//            }
//            default:{
//                return 0;
//            }
//        }
//    }
    return 0;
}
