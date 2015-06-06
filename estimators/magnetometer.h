#ifndef MAGNETOMETER_H_
#define MAGNETOMETER_H_

#include "TrigonomeC/my_math.h"

void get_estimated_error_magne(struct Quaternion4f q, struct Vector3f *ris, struct Vector3f rawData);

#endif
