/*
 * dcm_conf.c
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#include "dcm_conf.h"

uint8_t get_next_acce(struct Vector3f* toFill){
	toFill->x = 0;
	toFill->y = 0;
	toFill->z = 0;
	return 0;
}

uint8_t get_next_magne(struct Vector3f* toFill){
	toFill->x = 0;
	toFill->y = 0;
	toFill->z = 0;
	return 0;
}

struct error_estimator sensors[] = { {&get_next_acce, &get_estimated_error_acce}, {&get_next_magne, &get_estimated_error_magne} };
size_t sensors_size = sizeof(sensors)/sizeof(sensors[0]);
