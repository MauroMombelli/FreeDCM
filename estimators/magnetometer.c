/*
 * magnetometer.c
 *
 *  Created on: 09/mag/2015
 *      Author: mauro
 */

#include "magnetometer.h"

extern struct tmp_data tmp_shared;
extern struct Vector3f raw_data;
extern struct Vector3f halfe;

void get_estimated_error_magne() {

    if (raw_data.x != 0.0f || raw_data.y != 0.0f || raw_data.z != 0.0f) {
        float hx, hy, bx, bz;
        float halfwx, halfwy, halfwz;

        /* Normalize magnetometer measurement */
        float recipNorm = invSqrt(raw_data.x * raw_data.x + raw_data.y * raw_data.y + raw_data.z * raw_data.z);
        raw_data.x *= recipNorm;
        raw_data.y *= recipNorm;
        raw_data.z *= recipNorm;

        /* Reference direction of Earth's magnetic field */
        hx = 2.0f * (raw_data.x * (0.5f - tmp_shared.q2q2 - tmp_shared.q3q3) + raw_data.y * (tmp_shared.q1q2 - tmp_shared.q0q3) + raw_data.z * (tmp_shared.q1q3 + tmp_shared.q0q2));
        hy = 2.0f * (raw_data.x * (tmp_shared.q1q2 + tmp_shared.q0q3) + raw_data.y * (0.5f - tmp_shared.q1q1 - tmp_shared.q3q3) + raw_data.z * (tmp_shared.q2q3 - tmp_shared.q0q1));
        bx = sqrtf(hx * hx + hy * hy);
        bz = 2.0f * (raw_data.x * (tmp_shared.q1q3 - tmp_shared.q0q2) + raw_data.y * (tmp_shared.q2q3 + tmp_shared.q0q1) + raw_data.z * (0.5f - tmp_shared.q1q1 - tmp_shared.q2q2));

        /* Estimated direction of magnetic field */
        halfwx = bx * (0.5f - tmp_shared.q2q2 - tmp_shared.q3q3) + bz * (tmp_shared.q1q3 - tmp_shared.q0q2);
        halfwy = bx * (tmp_shared.q1q2 - tmp_shared.q0q3) + bz * (tmp_shared.q0q1 + tmp_shared.q2q3);
        halfwz = bx * (tmp_shared.q0q2 + tmp_shared.q1q3) + bz * (0.5f - tmp_shared.q1q1 - tmp_shared.q2q2);

        /* Error is sum of cross product between estimated direction and measured direction of field vectors */
        halfe.x += (raw_data.y * halfwz - raw_data.z * halfwy);
        halfe.y += (raw_data.z * halfwx - raw_data.x * halfwz);
        halfe.z += (raw_data.x * halfwy - raw_data.y * halfwx);
    }
}
