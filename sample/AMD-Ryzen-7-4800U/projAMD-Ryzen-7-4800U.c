/*
 ============================================================================
 Name        : projAMD-Ryzen-7-4800U.c
 Author      : OpenEL-WG
 Version     :
 Copyright   : Your copyright notice
 Description : Sample program for AMD-Ryzen-7-4800U temperature reading
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "openEL.h"

HALCOMPONENT_T *halSensor01;
HALEVENTTIMER_T HalEvtTm100;
HALEVENTTIMER_T *halTvtTm100 = &HalEvtTm100;


void cbNotifyTimer101(HALEVENTTIMER_T *eventTimer);
HALTIMEROBSERVER_T tmObs101 = { { 0 }, cbNotifyTimer101 };

int32_t event_count1;
HALFLOAT_T simVal1,simVal2;
int32_t tmSensor;

void outProperty(HALCOMPONENT_T *hC);

int main(void) {
	int32_t timeWk;
	uint8_t flgObs;

	printf("openEL Start\n");

	halSensor01 = HalCreate(0x0008,0x0000000C,0x00000001,1);

	HalInit(halSensor01);

	outProperty(halSensor01);

	printf("sensor01 getTime ret=%d\n", HalGetTime(halSensor01,&timeWk) );
	printf("Sensor time = %d\n",timeWk);

	HalEventTimerSetEventPeriod(halTvtTm100,100);
	HalEventTimerAddObserver(halTvtTm100,&tmObs101);
	HalEventTimerStartTimer(halTvtTm100);

	// ループ
	while(1) {
		usleep(500000); /* 0.5s */
		printf("timer %6d: ",event_count1);
		printf("%7.3lf %7.3lf %5d(tmSen)\n",simVal1,simVal2,tmSensor);
		fflush(stdout);
		if( 300 <= event_count1 ) break;
	}
	HalGetTime(halSensor01,&timeWk);
	printf("Sensor time = %d\n",timeWk);

	HalEventTimerStopTimer(halTvtTm100);
	HalEventTimerRemoveObserver(halTvtTm100,&tmObs101);

	HalFinalize(halSensor01);

	HalDestroy(halSensor01);

	printf("openEL End\n");
	return EXIT_SUCCESS;
}

void cbNotifyTimer101(HALEVENTTIMER_T *eventTimer) {
	double ph;
    int32_t idxPh;
	int32_t size;

	event_count1++;
	HalSensorGetValueList(halSensor01,&size,&simVal1);
	HalSensorGetTimedValueList(halSensor01,&size,&simVal2,&tmSensor);
}

void outProperty(HALCOMPONENT_T *hC) {
	int32_t i;
	HALPROPERTY_T propertyWk , *property;

	property = &propertyWk;
	HalGetProperty(hC,&propertyWk);
	printf("PROPERTY - Name : %s\n",property->deviceName);
	for ( i=0; i<property->sizeFunctionList; i++ ) {
		printf("PROPERTY - fnc%02X : %s\n",i,property->functionList[i]);
	}
}
