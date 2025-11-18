#pragma once

#include <cstdint>

uint16_t computeHeatingTime(const uint8_t initialTemp, const uint8_t finalTemp);

/// Design-by-Contract wrapper for computeHeatingTime.
///
/// @param initialTemp    The starting temperature in Celsius.
/// @param finalTemp      The target temperature in Celsius.
/// @param time           Pointer to store the computed heating time in seconds.
///
/// @return true if the contract is satisfied and result is computed; false otherwise.
///
/// PRECONDITIONS:
///   - finalTemp >= initialTemp (monotonic heating; cooling not supported)
///   - time != nullptr (valid pointer for output)
///
/// POSTCONDITIONS (on success):
///   - *time = (finalTemp - initialTemp) * conversion_factor
///   - *time >= 0 (always non-negative)
///
/// POSTCONDITIONS (on failure):
///   - *time is unchanged (no side effects on contract violation)
///   - return value is false
///
/// INVARIANTS:
///   - Result fits in uint16_t (max deltaT ~255, fits easily)
bool computeHeatingTimeDbC(const uint8_t initialTemp, const uint8_t finalTemp, uint16_t* time);
