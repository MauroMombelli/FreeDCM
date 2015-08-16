/*
 * accelerometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "accelerometer.h"

extern struct tmp_data tmp_shared;
extern struct Vector3f raw_data;
extern struct Vector3f halfe;

struct Vector3f raw_data = { 0,0,0 };

void get_estimated_error_acce() {

    if (raw_data.x == 0.0f && raw_data.y == 0.0f && raw_data.z == 0.0f) {
        return;
    }

    /* Prevent math error, also if we are in PERFECT free-fall we can't predict nothing*/
    float halfvx, halfvy, halfvz;

    /* Normalize accelerometer measurement */
    float recipNorm = invSqrt(raw_data.x * raw_data.x + raw_data.y * raw_data.y + raw_data.z * raw_data.z);
    raw_data.x *= recipNorm;
    raw_data.y *= recipNorm;
    raw_data.z *= recipNorm;

    /* Estimated direction of gravity */
    halfvx = tmp_shared.q1q3 - tmp_shared.q0q2;
    halfvy = tmp_shared.q0q1 + tmp_shared.q2q3;
    halfvz = tmp_shared.q0q0 - 0.5f + tmp_shared.q3q3;

    /* Error is sum of cross product between estimated direction and measured direction of field vectors */
    halfe.x += (raw_data.y * halfvz - raw_data.z * halfvy);
    halfe.y += (raw_data.z * halfvx - raw_data.x * halfvz);
    halfe.z += (raw_data.x * halfvy - raw_data.y * halfvx);
}
