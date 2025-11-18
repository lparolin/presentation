#include <cstdint>
#include <iostream>


#include "heating.h"

int main() {
    const uint8_t initialTemperature = 50U;
    const uint8_t finalTemperature = 49U;

    const auto duration = computeHeatingTime(initialTemperature, finalTemperature);

    std::cout << "Duration: " << duration << ".\n";
    return 0;
}
