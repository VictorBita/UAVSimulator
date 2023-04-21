// UAVSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

#include "UAV.h"

int main() {
    unsigned int type;

    std::cout << "Choose sensor type (0 - digital, 1 - analog): ";
    std::cin >> type;

    if (0 == type || 1 == type) {
        try {
            UAV uav(type);

            uav.Dive(MAX_UAV_DEPTH - 2.0);
            uav.MaintainDepth(5);
            uav.Ascend(10.0);
            uav.Dive(MAX_UAV_DEPTH - 15.0);
            uav.Ascend(0.0);
        }
        catch (const std::exception& e) {
            std::cout << "Operation exception: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "invalid type." << std::endl;
    }

}

