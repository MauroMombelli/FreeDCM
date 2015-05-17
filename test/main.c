#include <stdio.h>
#include <stdlib.h>

#include "dcm/dcm.h"

#include "original/MahonyAHRS.h"
#include "float.h"

extern struct Vector3f gyroValue;
extern struct Vector3f acceValue;
extern struct Vector3f magneValue;
struct Quaternion4f ris;

void do_step(int i) {
	dcm_step(gyroValue);
	dcm_get_quaternion(&ris);

	MahonyAHRSupdate(gyroValue.x, gyroValue.y, gyroValue.z, acceValue.x,
			acceValue.y, acceValue.z, magneValue.x, magneValue.y, magneValue.z);


	if (ris.w != q0 || ris.x != q1 || ris.y != q2 || ris.z != q3) {
		printf("\nstep %i", i);
		printf(" my_quat(%.9g,%.9g,%.9g,%.9g)", ris.w, ris.x, ris.y, ris.z);
		printf(" Mahony (%.9g,%.9g,%.9g,%.9g)", q0, q1, q2, q3);

		printf("\nERROR!");
		exit(1);
	}

	if (i%1000000 == 0){
		printf("\nstep %i OK", i);
	}
}

int main() {
	printf("\ninitializingDCM");
	dcm_init();

	dcm_get_quaternion(&ris);
	printf("\nstepping DCM");
	printf("\nstart_quat (%f,%f,%f,%f)", ris.w, ris.x, ris.y, ris.z);

	uint32_t i = 0;

	for (i = 0; i < 10; i++) {
		gyroValue.x = i;
		acceValue.x = i;
		magneValue.x = i;
		do_step(i);
	}

	while (1) {
		gyroValue.x = rand();
		gyroValue.y = rand();
		gyroValue.z = rand();
		acceValue.x = rand();
		acceValue.y = rand();
		acceValue.z = rand();
		magneValue.x = rand();
		magneValue.y = rand();
		magneValue.z = rand();
		do_step(i++);
	}

	while (1) {
		i++;
		/* ask for gyro */
		scanf("%f, %f, %f", &(gyroValue.x), &(gyroValue.y), &(gyroValue.z));
		/* ask for acce */
		scanf("%f, %f, %f", &(acceValue.x), &(acceValue.y), &(acceValue.z));
		/* ask for magne */
		scanf("%f, %f, %f", &(magneValue.x), &(magneValue.y), &(magneValue.z));

		do_step(i);
	}
	return 0;
}
