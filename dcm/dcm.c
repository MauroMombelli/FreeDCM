/*
 * dcm.c
 *
 *  Created on: Dec 8, 2014
 *      Author: mauro
 */

#include "dcm.h"

extern struct error_estimator sensors[];
extern size_t sensors_size;

/* PID factor */
float twoKp = 2.0f * 0.5f;
float twoKi = 2.0f * 0.0f;

/* frequency of sensor reading */
const float sample_freq = 355;

/* Quaternion */
struct Quaternion4f q;

/* integral result */
struct Vector3f integralFB;

void dcm_init(){
	q.w = 1;
	q.x = q.y = q.z = 0;

	integralFB.x = integralFB.y = integralFB.z = 0;
}

void dcm_step(struct Vector3f g) {

	float recipNorm;

	struct Vector3f tmp_raw_data;
	struct Vector3f halfe;
	halfe.x = halfe.y = halfe.z = 0;

	size_t i;
	for (i=0; i<sensors_size; i++){
		/* IF there is new raw data (get_raw_data == 0) then use it for estimation */
		if (! (*sensors[i].get_raw_data)(&tmp_raw_data) ){
			(*sensors[i].get_estimated_error)(q, &halfe, tmp_raw_data);
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
		}

		// Apply proportional feedback
		g.x += twoKp * halfe.x;
		g.y += twoKp * halfe.y;
		g.z += twoKp * halfe.z;
	}else{
		return;
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

void dcm_get_quaternion(struct Quaternion4f *qRis){
	qRis->w = q.w;
	qRis->x = q.x;
	qRis->y = q.y;
	qRis->z = q.z;
}
