/*
 * Tracking.h
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#ifndef TRACKING_H_
#define TRACKING_H_

#define MAX_TRACKINGS 5
#define FREE 0
#define INPROCESS 1
#define DELIVERED 2
#define CANCELLED -2

#include "General.h"

typedef struct {
	int idTracking;
	int idProduct;
	int idBuyer;
	int idSeller;
	short int isEmpty;

	int quantity;
	int distanceKM;
	long int arrivingTime;
	long int timeOfBought;
} Tracking;

int Tracking_initializeTrackings(Tracking trackingList[], int size);
void Tracking_printOne(Tracking track);
int Tracking_SearchSpace(Tracking trackingList[], int size, int status);
int Tracking_SearchIndexPerId(Tracking trackingList[], int trackingSize,
		int idBuyer);
int Tracking_PrintAndRefreshTrackings(Tracking trackingList[], int size);
#endif /* TRACKING_H_ */
