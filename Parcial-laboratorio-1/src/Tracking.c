/*
 * Tracking.c
 *
 *  Created on: 14 may 2022
 *      Author: gonza
 */

#include "Tracking.h"
#include "TimeFunctions.h"

int Tracking_initializeTrackings(Tracking *trackingList, int size) {
	int r = -1;
	int i;

	if (trackingList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			trackingList[i].isEmpty = FREE;
		}
	}
	return r;
}

void Tracking_printOne(Tracking track) {
	printf("Tracking ID: %d\nID Comprador: %d\nID Vendedor: %d\n",
			track.idTracking, track.idBuyer, track.idSeller);
	if (track.isEmpty == 1) {
		printf("Estado: EN PROCESO");
	} else {
		if (track.isEmpty == 2) {
			printf("Estado: ENTREGADO");
		} else {
			if (track.isEmpty == -2) {
				printf("Estado: CANCELADO");
			}
		}
	}
}

int Tracking_SearchSpace(Tracking trackingList[], int size, int status) {
	int r = -1;
	int i;

	if (trackingList != NULL && size > 0) {
		for (i = 0; i <= size; i++) {
			if (trackingList[i].isEmpty == status) {
				r = i;
				break;
			}
		}
	}
	return r;
}

int Tracking_SearchIndexPerId(Tracking trackingList[], int size, int ID) {
	int r = -1;
	int i;

	if (trackingList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			if (trackingList[i].idBuyer
					== ID&& trackingList[i].isEmpty == INPROCESS) {
				r = i;
				break;
			}
		}
	}

	return r;
}

int Tracking_PrintAndRefreshTrackings(Tracking trackingList[], int size) {
	int r = -1;
	int i;

	if (trackingList != NULL && size > 0) {
		for (i = 0; i < size; i++) {
			if (trackingList[i].isEmpty != 0) {
				if (trackingList[i].arrivingTime < time_Current()) {
					trackingList[i].isEmpty = DELIVERED;
				}
				Tracking_printOne(trackingList[i]);
			}
		}
		r = 0;
	}

	return r;
}

