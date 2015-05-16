/*
 * magnetometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "magnetometer.h"

struct Vector3f zero_magne = { 0, 0, 0 };
uint8_t last_update_m = 0;

void get_estimated_error_magne(struct Quaternion4f q, struct Vector3f *ris) {
	struct raw_magnetometer tmpM;
	uint8_t update = get_raw_magnetometer(&tmpM);
	//to float
	struct Vector3f tmp;
	tmp.x = tmpM.x - zero_magne.x;
	tmp.y = tmpM.y - zero_magne.y;
	tmp.z = tmpM.z - zero_magne.z;
	update -= last_update_m; //now in update there is the diff
	if ( update && (tmp.x != 0.0f || tmp.y != 0.0f || tmp.z != 0.0f)) {
		last_update_m += update; //now last_update_m is equal to update prior the diff

		float hx, hy, bx, bz;
		float halfwx, halfwy, halfwz;

		// Normalise magnetometer measurement
		float recipNorm = invSqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
		tmp.x *= recipNorm;
		tmp.y *= recipNorm;
		tmp.z *= recipNorm;

		// Reference direction of Earth's magnetic field
		hx = 2.0f * (tmp.x * (0.5f - q.y * q.y - q.z * q.z) + tmp.y * (q.x * q.y - q.w * q.z) + tmp.z * (q.x * q.z + q.w * q.y));
		hy = 2.0f * (tmp.x * (q.x * q.y + q.w * q.z) + tmp.y * (0.5f - q.x * q.x - q.z * q.z) + tmp.z * (q.y * q.z - q.w * q.x));
		bx = sqrtf(hx * hx + hy * hy);
		bz = 2.0f * (tmp.x * (q.x * q.z - q.w * q.y) + tmp.y * (q.y * q.z + q.w * q.x) + tmp.z * (0.5f - q.x * q.x - q.y * q.y));

		// Estimated direction of magnetic field
		halfwx = bx * (0.5f - q.y * q.y - q.z * q.z) + bz * (q.x * q.z - q.w * q.y);
		halfwy = bx * (q.x * q.y - q.w * q.z) + bz * (q.w * q.x + q.y * q.z);
		halfwz = bx * (q.w * q.y + q.x * q.z) + bz * (0.5f - q.x * q.x - q.y * q.y);

		// Normalize estimated reference field
		float norm = invSqrt(halfwx * halfwx + halfwy * halfwy + halfwz * halfwz);
		halfwx *= norm;
		halfwy *= norm;
		halfwz *= norm;

		// Error is sum of cross product between estimated direction and measured direction of field vectors
		ris->x += (tmp.y * halfwz - tmp.z * halfwy);
		ris->y += (tmp.z * halfwx - tmp.x * halfwz);
		ris->z += (tmp.x * halfwy - tmp.y * halfwx);
	}
}
