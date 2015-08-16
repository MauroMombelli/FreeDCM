#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "TrigonomeC/my_math.h"

void get_estimated_error_acce(const struct Quaternion4f* const q, const struct Vector3f* const raw_data, struct Vector3f* const ris);

#endif
