/*
 * TimeFunctions.h
 *
 *  Created on: 15 may 2022
 *      Author: gonza
 */

#ifndef TIMEFUNCTIONS_H_
#define TIMEFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CalculateDistance(int postalCode, int *kilometers);

long int time_Current(void);

long int time_Add(double secondsAdd);

int CalculateArrivalTime(int kilometers, long int *timeArrival);

#endif /* TIMEFUNCTIONS_H_ */
