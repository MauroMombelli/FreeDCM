/*
 * dcm_conf.h
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#ifndef DCM_CONF_H_
#define DCM_CONF_H_

#include "dcm.h"
#include "my_math/my_math.h"

uint8_t get_next_acce(struct Vector3f* toFill);
uint8_t get_next_magne(struct Vector3f* toFill);

#endif /* DCM_CONF_H_ */
