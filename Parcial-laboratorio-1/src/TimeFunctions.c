/*
 * TimeFunctions.c
 *
 *  Created on: 15 may 2022
 *      Author: gonza
 */
#include "TimeFunctions.h"

int CalculateDistance(int postalCode, int *kilometers) {
	int r = -1;
	if (postalCode > 0) {
		r = 0;
		if (postalCode <= 1000) {
			*kilometers = 20;
		} else {
			if (postalCode <= 3000) {
				*kilometers = 30;
			} else {
				if (postalCode <= 5000) {
					*kilometers = 50;
				} else {
					if (postalCode <= 8000) {
						*kilometers = 80;
					} else {
						*kilometers = 150;
					}
				}
			}
		}
	}

	return r;
}

long int time_Current(void){
	return time(NULL);
}

long int time_Add(double secondsAdd) {
	return secondsAdd + time_Current();
}

int CalculateArrivalTime(int kilometers, long int *timeArrival) {
	int r = -1;
	long int secondsToAdd = 0;
	for (int i = 1; i <= kilometers; i++) {
		if (i % 10 == 0) {
			secondsToAdd = secondsToAdd + 20;
		}
	}
	*timeArrival = time_Add(secondsToAdd);
	return r;
}
