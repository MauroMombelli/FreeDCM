/*
 * accelerometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "accelerometer.h"

struct Vector3f zero_acce = {-4089.385,5226.89,7490.706666666667};

void get_estimated_error_acce(struct Quaternion4f q, struct Vector3f *ris, struct Vector3f rawData) {

	rawData.x -= zero_acce.x;
	rawData.y -= zero_acce.y;
	rawData.z -= zero_acce.z;

	/* Prevent math error, also if we are in PERFECT free-fall we can't predict nothing*/
	if ( rawData.x != 0.0f || rawData.y != 0.0f || rawData.z != 0.0f ) {
		float halfvx, halfvy, halfvz;

		/* Normalize accelerometer measurement */
		float recipNorm = invSqrt(rawData.x * rawData.x + rawData.y * rawData.y + rawData.z * rawData.z);
		rawData.x *= recipNorm;
		rawData.y *= recipNorm;
		rawData.z *= recipNorm;

		/* Estimated direction of gravity */
		halfvx = q.x * q.z - q.w * q.y;
		halfvy = q.w * q.x + q.y * q.z;
		halfvz = q.w * q.w - 0.5f + q.z * q.z;

		/* Error is sum of cross product between estimated direction and measured direction of field vectors */
		ris->x += (rawData.y * halfvz - rawData.z * halfvy);
		ris->y += (rawData.z * halfvx - rawData.x * halfvz);
		ris->z += (rawData.x * halfvy - rawData.y * halfvx);

	}
}
