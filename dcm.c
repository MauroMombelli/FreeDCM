/*
 * dcm.c
 *
 *  Created on: Dec 8, 2014
 *      Author: mauro
 */

#include "dcm.h"

/* PID factor */
float twoKp = 2.0f * 0.5f;
float twoKi = 2.0f * 0.0f;

/* frequency of sensor reading */
const float sample_freq = 355.0f;

/* integral result */
struct Vector3f integralFB = { 0, 0, 0 };

extern struct Quaternion4f q;
extern struct Vector3f halfe;
extern struct tmp_data tmp_shared;
extern struct Vector3f raw_data;

void dcm_init() {
    q.w = 1;
    q.x = q.y = q.z = 0;

    integralFB.x = integralFB.y = integralFB.z = 0;
}

float recipNorm;
struct Vector3f g;
size_t i;

void dcm_step(const struct sensors* const sensors) {

    halfe.x = halfe.y = halfe.z = 0;

    // Auxiliary variables to avoid repeated arithmetic
    tmp_shared.q0q0 = q.w * q.w;
    tmp_shared.q0q1 = q.w * q.x;
    tmp_shared.q0q2 = q.w * q.y;
    tmp_shared.q0q3 = q.w * q.z;
    tmp_shared.q1q1 = q.x * q.x;
    tmp_shared.q1q2 = q.x * q.y;
    tmp_shared.q1q3 = q.x * q.z;
    tmp_shared.q2q2 = q.y * q.y;
    tmp_shared.q2q3 = q.y * q.z;
    tmp_shared.q3q3 = q.z * q.z;

    for (i = 0; i < sensors->sensors_number; i++) {
        switch (sensors->sensors[i].type) {
        case GYROSCOPE:
            g = *sensors->sensors[i].last_data; //shallow copy!
            break;
        case ACCELEROMETER:
            raw_data = *sensors->sensors[i].last_data; //shallow copy!
            get_estimated_error_acce();
            break;
        case MAGNETOMETER:
            raw_data = *sensors->sensors[i].last_data; //shallow copy!
            get_estimated_error_magne();
            break;
        }
    }

    // Apply feedback only when valid data has been gathered from sensors
    if (halfe.x != 0.0f || halfe.y != 0.0f || halfe.z != 0.0f) {
        // Compute and apply integral feedback if enabled
        if (twoKi > 0.0f) {
            integralFB.x += twoKi * halfe.x * (1.0f / sample_freq);  // integral error scaled by Ki
            integralFB.y += twoKi * halfe.y * (1.0f / sample_freq);
            integralFB.z += twoKi * halfe.z * (1.0f / sample_freq);
            g.x += integralFB.x;  // apply integral feedback
            g.y += integralFB.y;
            g.z += integralFB.z;
        } else {
            integralFB.x = 0.0f;	// prevent integral windup
            integralFB.y = 0.0f;
            integralFB.z = 0.0f;
        }

        // Apply proportional feedback
        g.x += twoKp * halfe.x;
        g.y += twoKp * halfe.y;
        g.z += twoKp * halfe.z;
    }

    // Integrate rate of change of quaternion
    g.x *= (0.5f * (1.0f / sample_freq));   // pre-multiply common factors
    g.y *= (0.5f * (1.0f / sample_freq));
    g.z *= (0.5f * (1.0f / sample_freq));

    float qa, qb, qc;
    qa = q.w;
    qb = q.x;
    qc = q.y;
    q.w += (-qb * g.x - qc * g.y - q.z * g.z);
    q.x += (qa * g.x + qc * g.z - q.z * g.y);
    q.y += (qa * g.y - qb * g.z + q.z * g.x);
    q.z += (qa * g.z + qb * g.y - qc * g.x);

    // Normalise quaternion
    recipNorm = invSqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    q.w *= recipNorm;
    q.x *= recipNorm;
    q.y *= recipNorm;
    q.z *= recipNorm;
}

void dcm_get_quaternion(struct Quaternion4f* const qRis) {
    qRis->w = q.w;
    qRis->x = q.x;
    qRis->y = q.y;
    qRis->z = q.z;
}

const struct DCM_s DCM = { &dcm_init, &dcm_step, &dcm_get_quaternion };
