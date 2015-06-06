/*
 * magnetometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "magnetometer.h"

struct Vector3f zero_magne = { 0, 0, 0 };
uint8_t last_update_m = 0;

void get_estimated_error_magne(struct Quaternion4f q, struct Vector3f *ris, struct Vector3f rawData) {

	rawData.x -= zero_magne.x;
	rawData.y -= zero_magne.y;
	rawData.z -= zero_magne.z;

	if ( rawData.x != 0.0f || rawData.y != 0.0f || rawData.z != 0.0f ) {
		float hx, hy, bx, bz;
		float halfwx, halfwy, halfwz;

		/* Normalize magnetometer measurement */
		float recipNorm = invSqrt(rawData.x * rawData.x + rawData.y * rawData.y + rawData.z * rawData.z);
		rawData.x *= recipNorm;
		rawData.y *= recipNorm;
		rawData.z *= recipNorm;

		/* Reference direction of Earth's magnetic field */
		hx = 2.0f * (rawData.x * (0.5f - q.y * q.y - q.z * q.z) + rawData.y * (q.x * q.y - q.w * q.z) + rawData.z * (q.x * q.z + q.w * q.y));
		hy = 2.0f * (rawData.x * (q.x * q.y + q.w * q.z) + rawData.y * (0.5f - q.x * q.x - q.z * q.z) + rawData.z * (q.y * q.z - q.w * q.x));
		bx = sqrtf(hx * hx + hy * hy);
		bz = 2.0f * (rawData.x * (q.x * q.z - q.w * q.y) + rawData.y * (q.y * q.z + q.w * q.x) + rawData.z * (0.5f - q.x * q.x - q.y * q.y));

		/* Estimated direction of magnetic field */
		halfwx = bx * (0.5f - q.y * q.y - q.z * q.z) + bz * (q.x * q.z - q.w * q.y);
		halfwy = bx * (q.x * q.y - q.w * q.z) + bz * (q.w * q.x + q.y * q.z);
		halfwz = bx * (q.w * q.y + q.x * q.z) + bz * (0.5f - q.x * q.x - q.y * q.y);

		/* Error is sum of cross product between estimated direction and measured direction of field vectors */
		ris->x += (rawData.y * halfwz - rawData.z * halfwy);
		ris->y += (rawData.z * halfwx - rawData.x * halfwz);
		ris->z += (rawData.x * halfwy - rawData.y * halfwx);
	}
}
