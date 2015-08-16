/*
 * accelerometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "accelerometer.h"

struct Vector3f zero_acce = { 0, 0, 0 };

void get_estimated_error_acce(const struct Quaternion4f* const q, const struct Vector3f* const raw_data, struct Vector3f* const ris) {

    if (raw_data->x == 0.0f && raw_data->y == 0.0f && raw_data->z == 0.0f) {
        return;
    }

    struct Vector3f rawData = { raw_data->x, raw_data->y, raw_data->z };

    rawData.x -= zero_acce.x;
    rawData.y -= zero_acce.y;
    rawData.z -= zero_acce.z;

    /* Prevent math error, also if we are in PERFECT free-fall we can't predict nothing*/
    float halfvx, halfvy, halfvz;

    /* Normalize accelerometer measurement */
    float recipNorm = invSqrt(rawData.x * rawData.x + rawData.y * rawData.y + rawData.z * rawData.z);
    rawData.x *= recipNorm;
    rawData.y *= recipNorm;
    rawData.z *= recipNorm;

    /* Estimated direction of gravity */
    halfvx = q->x * q->z - q->w * q->y;
    halfvy = q->w * q->x + q->y * q->z;
    halfvz = q->w * q->w - 0.5f + q->z * q->z;

    /* Error is sum of cross product between estimated direction and measured direction of field vectors */
    ris->x += (rawData.y * halfvz - rawData.z * halfvy);
    ris->y += (rawData.z * halfvx - rawData.x * halfvz);
    ris->z += (rawData.x * halfvy - rawData.y * halfvx);
}
