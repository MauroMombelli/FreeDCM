#include <stdio.h>

#include "dcm/dcm.h"


int main(){
	printf("initializingDCM\n");
	dcm_init();



	struct Vector3f gyroValue = {0, 0, 0};
	struct Vector3f acceValue = {0, 0, 0};
	struct Vector3f magneValue = {0, 0, 0};

	struct Quaternion4f ris;
	dcm_get_quaternion(&ris);
	printf("stepping DCM\n");
	printf("start_quat (%f,%f,%f,%f)\n", ris.w, ris.x, ris.y, ris.z);

	uint32_t i=0;
	while (1){
		i++;
		/* ask for gyro */
		scanf("%f, %f, %f", &(gyroValue.x), &(gyroValue.y), &(gyroValue.z));
		/* ask for acce */
		scanf("%f, %f, %f", &(acceValue.x), &(acceValue.y), &(acceValue.z));
		/* ask for magne */
		scanf("%f, %f, %f", &(magneValue.x), &(magneValue.y), &(magneValue.z));

		/*printf ("step %i gyro (%f,%f,%f)\n", i, gyroValue.x, gyroValue.y, gyroValue.z);*/
		dcm_step(gyroValue);
		dcm_get_quaternion(&ris);
		printf ("step %i quat (%f,%f,%f,%f)\n", i,  ris.w, ris.x, ris.y, ris.z);
	}
	return 0;
}
