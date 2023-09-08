/*
 ============================================================================
 Name        : getCPUTemp.c
 Author      : OpenEL-WG
 Version     :
 Copyright   : Your copyright notice
 Description : Program for AMD-Ryzen-7-4800U temperature reading
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "openEL.h"

HALCOMPONENT_T *halSensor01;
HALFLOAT_T simVal1;

int main(void) {
    int32_t timeWk;
    int32_t size;
    uint8_t flgObs;

    halSensor01 = HalCreate(0x0008,0x0000000C,0x00000001,1);

    HalInit(halSensor01);

    HalSensorGetValueList(halSensor01,&size,&simVal1);

    printf("%4.1f\u2103\n",simVal1);
    fflush(stdout);

    HalFinalize(halSensor01);

    HalDestroy(halSensor01);

    return EXIT_SUCCESS;
}
