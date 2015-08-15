#ifndef MAGNETOMETER_H_
#define MAGNETOMETER_H_

#include "TrigonomeC/my_math.h"

uint8_t get_estimated_error_magne(const struct Quaternion4f* const q, const struct Vector3f* const raw_data, struct Vector3f* const ris);

#endif
