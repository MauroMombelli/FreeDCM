/*
 * l3g4200d.h
 *
 *  Created on: May 28, 2014
 *      Author: mauro
 */

#ifndef DCM_H_
#define DCM_H_

//#include "../../driver_sensors/lsm303dlhc.h"

#include <stdint.h>
#include <stddef.h>

#include "my_math/my_math.h"
#include "estimators/accelerometer.h"
#include "estimators/magnetometer.h"

struct errori{
	void (*get_estimated_error)(struct Quaternion4f, struct Vector3f*);
};

void dcm_init(void);
void dcm_step(struct Vector3f);
void dcm_get_quaternion(struct Quaternion4f *);

#endif /* DCM_H_ */
