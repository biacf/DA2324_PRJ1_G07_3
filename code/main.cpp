#include <iostream>
#include "WaterNetwork.h"
int main() {

    WaterNetwork waterNetwork;
    char option;

    std::cout << "##################################################" << std::endl;
    std::cout << "Welcome to the L.EIC Water Supply Management Tool!" << std::endl;
    std::cout << "##################################################" << std::endl;

    while(true){
        std::cout << "\nWhat would you like to simulate today?" << std::endl;
        std::cout << "\na. Load data to be parsed" << std::endl;
        std::cout << "b. Check Maximum Flow options" << std::endl;
        std::cout << "c. Check under supplied cities" << std::endl;
        std::cout << "d. Remove Water Reservoirs" << std::endl;
        std::cout << "e. Remove Pumping Stations" << std::endl;
        std::cout << "f. Vital Pipelines" << std::endl;
        std::cout << "g. Remove pipelines" << std::endl;
        std::cout << "h. Exit" << std::endl;

        std::cout << "\nOption: ";
        std::cin >> option;
        while(option < 'a' || option > 'h'){
            std::cout << "\nOption: ";
            std::cin >> option;
        }

        switch(option){
            case 'h':{
                return 0;
            }
            default:{
                return 0;
            }
        }
    }
}
