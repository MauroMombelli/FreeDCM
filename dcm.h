/*
 * l3g4200d.h
 *
 *  Created on: May 28, 2014
 *      Author: mauro
 */

#ifndef DCM_H_
#define DCM_H_

#include "TrigonomeC/my_math.h"

struct error_estimator {
    uint8_t (*get_isu_data)(struct Vector3f*); /* give data into International Standard Unit notation; acceleration are in m/s, rotation in rad/s, etc.. */
    uint8_t (*get_raw_data)(struct Vector3f*);
    void (*get_estimated_error)(struct Quaternion4f, struct Vector3f*, struct Vector3f);
};

struct DCM_s {
    void (*dcm_init)(void);
    void (*dcm_step)(struct Vector3f, struct error_estimator *, size_t);
    void (*dcm_get_quaternion)(struct Quaternion4f *);
};

extern struct DCM_s DCM;

#endif /* DCM_H_ */
