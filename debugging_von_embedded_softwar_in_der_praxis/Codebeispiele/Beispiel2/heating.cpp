#include "heating.h"

#include <cstdint>

uint16_t computeHeatingTime(const uint8_t initialTemp,
                            const uint8_t finalTemp)
{
    const uint8_t conversion_factor = 1; 
    const uint8_t deltaT = finalTemp - initialTemp;
    const uint16_t time_sec = static_cast<uint16_t>(conversion_factor) * static_cast<uint16_t>(deltaT);
    return time_sec;
}
