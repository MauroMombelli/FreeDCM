/*
 * l3g4200d.h
 *
 *  Created on: May 28, 2014
 *      Author: mauro
 */

#ifndef DCM_H_
#define DCM_H_

#include "TrigonomeC/my_math.h"
#include "dcm.h"
#include "estimators/accelerometer.h"
#include "estimators/magnetometer.h"
#include "estimators/shared.h"

enum sensor_type{
    ACCELEROMETER, MAGNETOMETER
};

struct error_estimator {
    /*
    uint8_t (*raw_to_is)(const struct Vector3f* const raw_value, struct Vector3f* const is_value); // give data into International Standard Unit notation; acceleration are in m/s, rotation in rad/s, etc..
    uint8_t (*get_raw_data)(struct Vector3f* const result);
    uint8_t (*get_estimated_error)(const struct Quaternion4f* const orientation, const struct Vector3f* const raw_value, struct Vector3f* const result);
    */
    enum sensor_type type;
    struct Vector3f* last_data;
};

struct sensors{
    const struct error_estimator* const sensors;
    const size_t sensors_number;
};

struct DCM_s {
    void (*dcm_init)(void);
    void (*dcm_step)(const struct Vector3f* const gyroscope, const struct sensors* const sensors);
    void (*dcm_get_quaternion)(struct Quaternion4f* const result);
};

extern const struct DCM_s DCM;

#endif /* DCM_H_ */
