/*
 * dcm_conf.c
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#include "dcm_conf.h"

struct Vector3f gyroValue = { 0, 0, 0 };
struct Vector3f acceValue = { 0, 0, 0 };
struct Vector3f magneValue = { 0, 0, 0 };

uint8_t get_next_acce(struct Vector3f* toFill){
	toFill->x = acceValue.x;
	toFill->y = acceValue.y;
	toFill->z = acceValue.z;
	return 0;
}

uint8_t get_next_magne(struct Vector3f* toFill){
	toFill->x = magneValue.x;
	toFill->y = magneValue.y;
	toFill->z = magneValue.z;
	return 0;
}

struct error_estimator sensors[] = { {&get_next_acce, &get_estimated_error_acce}, {&get_next_magne, &get_estimated_error_magne} };
size_t sensors_size = sizeof(sensors)/sizeof(sensors[0]);
